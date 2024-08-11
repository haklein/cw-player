#include "MorsePlayer.h"

std::string char2morse(char c)
{
	switch (toupper(c)) {
		case '=':
			return "-...-";
		case '+':
			return ".-.-.";
		case '-':
			return "-....-";
		case '_':
			return "..--.-";
		case '/':
			return "-..-.";
		case ':':
			return "---...";
		case ';':
			return "-.-.-.";
		case '!':
			return "-.-.--";
		case '?':
			return "..--..";
		case '\'':
			return ".----.";
		case '(':
			return "-.--.";
		case ')':
			return "-.--.-";
		case ',':
			return "--..--";
		case '.':
			return ".-.-.-";
		case '1':
			return ".----";
		case '2':
			return "..---";
		case '3':
			return "...--";
		case '4':
			return "....-";
		case '5':
			return ".....";
		case '6':
			return "-....";
		case '7':
			return "--...";
		case '8':
			return "---..";
		case '9':
			return "----.";
		case '0':
			return "-----";
		case 'A':
			return ".-";
		case 'B':
			return "-...";
		case 'C':
			return "-.-.";
		case 'D':
			return "-..";
		case 'E':
			return ".";
		case 'F':
			return "..-.";
		case 'G':
			return "--.";
		case 'H':
			return "....";
		case 'I':
			return "..";
		case 'J':
			return ".---";
		case 'K':
			return "-.-";
		case 'L':
			return ".-..";
		case 'M':
			return "--";
		case 'N':
			return "-.";
		case 'O':
			return "---";
		case 'P':
			return ".--.";
		case 'Q':
			return "--.-";
		case 'R':
			return ".-.";
		case 'S':
			return "...";
		case 'T':
			return "-";
		case 'U':
			return "..-";
		case 'V':
			return "...-";
		case 'W':
			return ".--";
		case 'X':
			return "-..-";
		case 'Y':
			return "-.--";
		case 'Z':
			return "--..";
		case '<':
		case '>':
			return "";
		default:
			return " ";
	}
}

MorsePlayer::MorsePlayer(sidetone_fun_ptr sidetone_cb) {
    this->sidetone_cb = sidetone_cb;
}

void MorsePlayer::play(const char *text, int wpm) {
	int dot_delay = 1200 / wpm; // wpm 
	static int cw_keyer_weight = 55;
	int dash_delay = (dot_delay * 3 * cw_keyer_weight) / 50;
	bool prosign = false;

	while (*text) {
		if (text[0] == '<') prosign=true;
		if (text[0] == '>') prosign=false;

		const char *c = char2morse(text[0]).c_str();
		while (*c) {
			switch (c[0]) {
				case '.':
					this->sidetone_cb(true);
					usleep(dot_delay*1000);
					this->sidetone_cb(false);
					break;
				case '-':
					this->sidetone_cb(true);
					usleep(dash_delay*1000);
					this->sidetone_cb(false);
					break;
			}
			c++;
			usleep(dot_delay * 1000);
		}
		text++;
		if (!prosign) usleep(dot_delay * 2 * 1000);	// 2 + inner loop = 3 times dot delay as space
	}
}
