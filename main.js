'use strict';

const Discord = require("discord.js");
const client = new Discord.Client();

let {readFileSync} = require('fs');

let token = readFileSync('./token.key').toString();

let util = require('./util.js');
let commands = require('./commands.js') || {};
let Server = require('./server.js');
let servers = {};

client.on('ready', function() {
	console.log(`Logged in as ${client.user.tag}!`);
	for(let guild in client.guilds)
		if(guild.available)
			servers[guild.id] = new Server(guild);
});
client.on('guildMemberAdd', function(newbie) {
	let serv = servers[newbie.guild.id];
	if(serv)
		serv.defaultChannel.send(`${newbie}, ${serv.get('welcome')}`);
});
client.on('messsage', function(msg) {
	let serv = servers[msg.guild.id];
	if(!serv) return;
	let prefix = serv.get('prefix');
	if(!msg.content.startsWith(prefix)) return;
	
	let content = msg.substr(prefix.length, msg.content.length);
	console.log(content);
	let args = argparse(content.replace(/\s+$/g, ''));
	let command = args.shift();
	if(command === "help") {
		//msg.author.send(util.formatHelpText(invoc, helpText[type]));
		return;
	}
	
	let func = commands[command];
	if(func) {
		(new Promise((resolve, reject) => {
			let result;
			try {
				result = func(msg, serv, args);
			}
			catch (err) {
				reject(err);
			}
			resolve(result);
		})).then(console.log).catch(console.error);
	}
	else
		console.log(`Unknown command ${command}`);
});

client.login(token);
