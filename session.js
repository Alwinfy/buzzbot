let sessions = {};
function Session(start, channel, types) {
	this.position = start;
	this.tried = false;
	this.channel = channel;
	this.types = types;
	sessions[channel.id] = this;
	buzzOnce(this.position, this.channel, this.types,
		this.win.bind(this), this.lose.bind(this));
}
Session.prototype.win = function() {
	if(!this.position) {
		delete sessions[this.channel.id];
		return;
	}
	this.position++;
	this.tried = false;
	this.channel.send('Correct! New number.')
	buzzOnce(this.position, this.channel, this.types,
		this.win.bind(this), this.lose.bind(this));
}
Session.prototype.lose = function() {
	if(!this.position) {
		delete sessions[this.channel.id];
		return;
	}
	if(this.tried) {
		this.channel.send(`Wrong again: we are on **${this.position}**. Try again.`);
	}
	else {
		this.tried = true;
		this.channel.send('Incorrect. Same number, second try.');
	}
	buzzOnce(this.position, this.channel, this.types,
		this.win.bind(this), this.lose.bind(this));
}
Session.stop = function(id) {
	sessions[id].position = undefined;
}

module.exports = Session;
