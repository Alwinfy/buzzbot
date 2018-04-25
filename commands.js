const discord = require('discord.js');
const Session = require('./session');
const {Ticket} = require('./ticket');
const Query = require('./query');
const query = new Query();
const {readFileSync} = require('fs');
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
	reply += `\n\nTo reply to the bot's prompt, prefix your answer with \`${serv.get('replypfx')}\`.`
	msg.channel.send(reply);
}, 'help', 'displays this help');
new Command(function(msg) {
	msg.channel.send(msg);
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
	let nums = args.filter(val => !isNaN(+val));
	query.query(nums.join(' '), rets => {
		let string = '', values = rets.split(' ');
		for(let i=0;i<nums.length;i++)
			if(values[i] !== 'Error')
				string += `**${nums[i]}** is \`${values[i] || nums[i]}\`.\n`;
		msg.channel.send(string || '*No valid positive integers detected.*');
	});
}, 'calc', 'calculates a BuzzWord');
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
}, 'ask', 'asks you to calculate a BuzzWord');

new Command(function(msg, serv, args) {
	let startpt = Math.floor(args[0] && args[0].includes('rand')
		? Math.random() *
			(serv.get('buzzmax') - serv.get('buzzmin'))
			+ serv.get('buzzmin')
		: +args[0] || 1);
	console.log(Session);
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
	msg.channel.send(`Enabled BuzzWords \`${succ.join('\` \`') || 'N/A'}\``);
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
	msg.channel.send(`Disabled BuzzWords \`${succ.join('\` \`') || 'N/A'}\``);
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
new Command(function(msg) {
	msg.channel.fetchMessages({limit: 100})
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


