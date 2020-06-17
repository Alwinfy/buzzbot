const discord = require('discord.js');
const Session = require('./session');
const {Ticket} = require('./ticket');
const Query = require('./query');
const query = new Query();
const {readFileSync} = require('fs');
const splitter = new (require('grapheme-splitter'))();
let commands = {};
function Command(callback, name, desc, visible=true) {
	this.call = callback;
	this.name = name;
	this.desc = desc;
	commands[this.name] = this;
	if(visible) {
		let pos;
		for(pos = 1; pos < this.name.length &&
			commands[this.name.substr(0, pos)]; pos++);
		commands[this.name.substr(0, pos)] = this;
	}
	else
		this.name += '\u200b';
}

const thonks = readFileSync('./thonks.txt').toString().split('\n');
const info = readFileSync('./info.txt').toString();

function buzzOnce(value, chan, types, win, lose) {
	query.query(value, str => {
		let values = {}, trueword = '';
		for(let type of types)
			if(values[type] = str.includes(type))
				trueword += type;
		return new Ticket('channel', chan.id, function(msg) {
			let lower = msg.content.toLowerCase();
			for(let type of types)
				if(lower.includes(type.toLowerCase()) != values[type]) {
					lose(trueword || value);
					return;
				}
			(trueword || RegExp(`\\b${value}\\b`).test(lower)
				? win : lose)(trueword || value);
		});
	});
}
Session.buzzOnce = buzzOnce;

new Command(function(msg, serv) {
	let reply = '**BuzzBot** - a bot for playing BuzzCount\n\n**__Commands:__**',
		prefix = serv.get('prefix');
	for(let cmd in commands)
		if(cmd === commands[cmd].name)
			reply += `\n\`${prefix}${cmd}\` - ${commands[cmd].desc}`;
	reply += `\n\nTo reply to the bot's prompt, prefix your answer with \`${serv.get('replypfx')}\`. Please note that any persistent commands (setmax, etc.) will not persist over a day.`
	msg.channel.send(reply);
}, 'help', 'displays this help');
new Command(function(msg, serv) {
	msg.channel.send(info.replace('PREFIX', serv.get('prefix'))
		.replace('REPLYPFX', serv.get('replypfx')));
}, 'info', 'displays general info about BuzzCount');
new Command(function(msg, serv) {
	let reply = '', types = [], bl = serv.get('blacklist');
	for(let name in query.types) {
		let line = `A number is **${name}** if it ${query.types[name]}.\n`;
		if(bl[name])
			line = `~~${line}~~`;
		reply += line;
	}
	msg.channel.send(reply);
}, 'list', 'lists all buzzwords');
new Command(function(msg, serv, args) {
	msg.channel.send('pong');
}, 'ping', 'tests if the bot is online');
new Command(function(msg, serv, args) {
	msg.channel.send('no u');
}, 'off', '>:(', false);
new Command(function(msg, serv, args) {
	if(args.join(' ').toLowerCase() === 'an alien')
		msg.channel.send('*WHERE?*');
}, 'look', 'looks at argument, under certain conditions', false);

new Command(function(msg, serv, args) {
	let nums = args.filter(val => !isNaN(+val));
	query.query(nums.join(' '), rets => {
		let string = '', values = rets.split(' ');
		for(let i=0;i<nums.length;i++)
			if(values[i] !== 'Error')
				string += `**${nums[i]}** is \`${values[i] || nums[i]}\`.\n`;
		msg.channel.send(string || '*No valid positive integers detected.*');
	});
}, 'calc', 'calculates the BuzzWords of a number');
new Command(function(msg, serv) {
	let value = Math.floor(Math.random() *
		(serv.get('buzzmax') - serv.get('buzzmin'))
		+ serv.get('buzzmin'));
	let types = [];
	let bl = serv.get('blacklist');
	for(let type in query.types)
		if(!bl[type])
			types.push(type);
	msg.channel.send(`Your number is **${value}**.`)
	buzzOnce(value, msg.channel, types,
		val => msg.channel.send('Correct!'),
		val => {
		msg.channel.send(`Incorrect: I was looking for \`${val}\`.`);});
}, 'ask', 'asks you to calculate the BuzzWords of a number');

new Command(function(msg, serv, args) {
	let max = serv.get('buzzmax'), min = serv.get('buzzmin');
	let startpt = Math.floor(args[0] && args[0].includes('rand')
		? Math.random() * (max - min) + min
		: Math.min(Math.max(+args[0] || 1, min), max));
	if(Session.get(msg.channel.id)) {
		msg.channel.send('Buzz game has already started!');
		return;
	}
	let types = [];
	let bl = serv.get('blacklist');
	for(let type in query.types)
		if(!bl[type])
			types.push(type);
	msg.channel.send(`Buzz game started! Beginning at **${startpt}**.`);
	new Session(startpt, msg.channel, types);
}, 'start', 'start a game of BuzzCount');

new Command(function(msg) {
	Session.stop(msg.channel.id);
}, 'stop', 'stop the current BuzzCount game');

new Command(function(msg, serv, args) {
	let bl = serv.get('blacklist');
	let succ = [];
	args.forEach(arg => {
		let cased = arg[0].toUpperCase() +
			arg.substr(1, arg.length).toLowerCase();
		if(bl[cased])
		{
			succ.push(cased);
			delete bl[cased];
		}
	});
	msg.channel.send(`Enabled BuzzWord(s) \`${succ.join('\` \`') || 'N/A'}\`.`);
	serv.set('blacklist', bl);
}, 'enable', 'enables a BuzzWord');
new Command(function(msg, serv, args) {
	let bl = serv.get('blacklist');
	let succ = [];
	args.forEach(arg => {
		let cased = arg[0].toUpperCase() +
			arg.substr(1, arg.length).toLowerCase();
		if(query.types[cased])
		{
			succ.push(cased);
			bl[cased] = true;
		}
	});
	msg.channel.send(`Disabled BuzzWord(s) \`${succ.join('\` \`') || 'N/A'}\`.`);
	serv.set('blacklist', bl);
}, 'disable', 'disables a BuzzWord from gameplay (calculations will still display it)');
new Command(function(msg, serv, args) {
	if(!args[0]) {
		msg.channel.send(`Currently, the maximum is **${serv.get('buzzmax')}.`)
		return;
	}
	let val = Math.floor(+args[0]);
	if(val && val > 1 && val < 1000000) {
		serv.set('buzzmax', val);
		msg.channel.send(`Successfully set new maximum to **${val}**!`);
	}
	else
		msg.channel.send(`Invalid value ${args[0]}.`);
}, 'setmax', 'sets the maximum number `ask` will give you');
new Command(function(msg, serv, args) {
	serv.set('welcome', args.join(' '));
}, 'setmsg', 'sets the server\'s welcome message', false);
new Command(function(msg, serv, args) {
	serv.set('replypfx', args[0] || '$');
}, 'setprefix', 'sets the server\'s bot reply prefix', false);
new Command(function(msg, serv, args) {
	let embed = new (discord.RichEmbed || discord.MessageEmbed);
	embed.setTitle('\uD83E\uDD14');
	embed.setImage(thonks[Math.floor(thonks.length * Math.random())]);
	msg.channel.send(embed);
}, 'thonk', 'replies with a random thonk emote');
new Command(function(msg, serv, args) {
	const MAXINFO = 40, MAXDICE = 10000, MAXROLL = 1e6;

	const str = args.join('');
	const split = str.split(/\+|(?=-)/);
	console.log(split);
	const kept = [], dropped = [];
	let count = 0, total = 0, math = 0;

	for(const roll of split) {
		if(!roll) continue;
		// parse
		const match = roll.match(/^(-?)([0-9]*)(?:d([0-9]+))?([ukld])?([0-9]*)(!?)$/i);
		if(!match)
			return msg.channel.send(`Got a bad diceroll: ${roll}!`);
		// parse & check conditions
		const mul = match[1] ? -1 : 1;
		const rolls = match[2] ? +match[2] : 1;
		if(!rolls) continue;
		count += rolls;
		if(count > MAXDICE)
			return msg.channel.send(`That's too many dice!`);
		if(!match[3]) {
			total += mul * rolls;
			math += mul * rolls;
			continue;
		}
		const sides = +match[3];
		if(sides < 2 || sides > MAXROLL)
			return msg.channel.send(`This bot has no ${sides}-sided dice.`);
		let keep = match[4] ? Math.min(rolls, Math.max(0, match[5] ? +match[5] : rolls - 1)) : rolls;
		if(match[4] === 'd')
			keep = rolls - keep;
		// do the rolls
		const therolls = new Array(rolls), thekeep = new Array(keep), thedrop = new Array(rolls - keep);
		for(let i=0; i<rolls; i++)
			therolls[i] = [i, 1 + Math.floor(Math.random() * sides)];
		therolls.sort(match[4] === 'l' ? ((a, b) => a[1] - b[1]) : ((a, b) => b[1] - a[1]));
		for(let i=0; i<keep; i++) {
			thekeep[i] = therolls[i];
			total += thekeep[i][1] * mul;
		}
		for(let i=keep; i<rolls; i++)
			thedrop[i - keep] = therolls[i];
		if(!match[6]) {
			thekeep.sort((a, b) => a[0] - b[0]);
			thedrop.sort((a, b) => a[0] - b[0]);
		}
		else {
			thekeep.sort((a, b) => a[1] - b[1]);
			thedrop.sort((a, b) => a[1] - b[1]);
		}
		kept.push([mul, thekeep]);
		if(thedrop.length)
			dropped.push(thedrop);
	}

	let message = `You roll \`${str}\` and get **${total}**.`;
	if((kept.length || dropped.length) && count <= MAXINFO) {
		message += ' ';
		if(kept.length >= 2 || kept[0][1].length >= 2 || dropped.length) {
			message += `${kept[0][0] == -1 ? '-' : ''}[ ${kept[0][1].map(x => x[1]).join(', ')} ]`;
			for(let i=1; i<kept.length; i++)
				message += ` ${kept[i][0] == -1 ? '-' : '+'} [ ${kept[i][1].map(x => x[1]).join(', ')} ]`;
			if(math) message += ` ${math > 0 ? '+' : '-'} ${Math.abs(math)}`;
		}
		if(dropped.length) {
			message += `, dropped [ ${dropped[0].map(x => x[1]).join(', ')} ]`;
			for(let i=1; i<dropped.length; i++)
				message += `& [ ${dropped[i].map(x => x[1]).join(', ')} ]`;
		}
	}
	msg.channel.send(message);
}, 'roll', 'rolls the specified DnD-style die');
new Command(function(msg, serv, args) {
	const MAXLEN = 2000;
	let str = args.join('').replace(/\s+/g, '').toUpperCase();
	if(str[0] !== str[str.length - 1])
		str = `*${str}*`;
	let string = splitter.splitGraphemes(str);
	if(string.length < 6) {
		msg.channel.send("Sorry, that string's too short!");
		return;
	}
	
	let lines = Math.floor(string.length / 8) + 1;
	let offset = Math.floor(string.length / (2 * lines));
	let height = string.length - 1;
	let depth = offset * lines;
	let size = depth + string.length;
	if(size * size * 2 > MAXLEN) {
		msg.channel.send("Phrase too long!");
		return;
	}

	let strings = [];
	for(let i=0; i<size; i++)
		strings.push(Array(size).fill(' '));
	for(let i=0; i<2; i++)
		for(let j=0; j<2; j++)
			for(let k=0; k<=depth; k++)
				strings[i * height + k]
					[j * height + depth - k] = '/';
	for(let i=0; i<=lines; i++)
		for(let j=0; j<string.length; j++)
			strings[i * offset + j][(lines - i) * offset] =
			strings[i * offset][(lines - i) * offset + j] =
			strings[i * offset + j][(lines - i) * offset + height] =
			strings[i * offset + height][(lines - i) * offset + j] =
				string[j];

	msg.channel.send('```\n' +
		strings.map(str => str.join(' ').replace(/\s+$/, '')).join('\n')
		+ '\n```');
}, 'cube', 'draws an ASCII cube using the specified text');
new Command(function(msg) {
	msg.channel.fetchMessages({limit: 50})
		.then(function(messages) {
			return messages.filter(function(message) {
				return message.author.id === message.client.user.id;
			});
		}).then(function(messages) {
			let lastKey = messages.lastKey();
			for(let message of messages) {
				if(message[0] === lastKey) {
					message[1].delete().then(function() {
						console.log('Deleted the last few messages.')
					})
				} else {
					message[1].delete()
				}
			}
		})	
}, 'clean', 'removes the last few bot replies');

module.exports = commands;


