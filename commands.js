let commands = {};
function Command(callback, name, desc) {
	this.call = callback;
	this.name = name;
	this.desc = desc;
	commands[this.name] = this;
	let pos;
	for(pos = 1; pos < this.name.length &&
		commands[this.name.substr(0, pos)]; pos++);
	commands[this.name.substr(0, pos)] = this;
}

Command.prototype.help = function() {
	return `${name} - ${desc}`;
}

new Command(function(msg, serv, args) {
	msg.channel.send('pong');
}, 'ping', 'tests if the bot is online');
module.exports = commands;
