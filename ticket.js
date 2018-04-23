let tickets = {}, tid = 0;

function Ticket(field, value, callback) {
	this.call = callback;
	this.value = value;
	this.field = field;
	tickets[tid++] = this;
}

Ticket.prototype.check = function(msg) {
	return msg[this.field].id == this.value;
}

function checkAll(msg) {
	for(let i in tickets)
		if(tickets[i].check(msg)) {
			tickets[i].call(msg);
			delete tickets[i];
		}
}

module.exports.Ticket = Ticket;
module.exports.checkAll = checkAll;
