
function argparse(str) {
	let spl = [''], esc = false, quot = true;
	for (let c of str) {
		if (esc) { // last character was a backslash, skip handling
			esc = false;
			spl[spl.length - 1] += '\\' + c;
			continue;
		}
		switch(c) {
		case '\\':
			esc = true; // escape next character
			break;
		case '"':
			quot = !quot;
			break;
		case ' ':
		case '\t':
			if (quot && spl[spl.length - 1]) {
				spl.push(''); // split on unquoted spaces
				break;
			}
		default:
			spl[spl.length - 1] += c;
		}
	}
	return spl;
}

module.exports = {argparse: argparse};
