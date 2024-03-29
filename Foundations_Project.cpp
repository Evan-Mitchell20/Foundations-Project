#include <iostream>
#include <vector>

using namespace std;

class Character
{
public:
	Character(char a)
	{
		character = a;
	}
	char32_t character;
};

class String
{
public:
	vector<Character> string;
};

class Alphabet
{
public:
	Alphabet() {}
	Alphabet(vector<Character> a)
	{
		alphabet = a;
	}
	Character next_char(Character c)
	{
		for (int i = 0; i < alphabet.size(); i++)
		{
			if (alphabet[i].character == c.character)
			return this->alphabet[i + 1];
		}
		cout << "next character not reachable.";
	}
	Character at(int index)
	{ 
		return this->alphabet[index];
	}
	int size()
	{ 
		return this->alphabet.size();
	}
	vector<Character> alphabet;
};

String Generate_nth_str_helper(int n, Alphabet a, String str)
{
	if (n == 1)
	{
		return str;
	}
	String max, result;

	for (int i = 0; i < str.string.size(); i++)
	{
		max.string.push_back(a.alphabet.back()); //max string of size 3 ex: "zzz"
	}
	if (str.string == max.string)
	{
		for (int i = 0; i < str.string.size() + 1; i++)
		{
			result.string.push_back(a.alphabet[0]); //"zzz" -> "aaaa"
		}
		Generate_nth_str_helper(--n, a, result); //call with "aaaa"
	}
	for (int i = str.string.size() - 1; i >= 0; i--)
	{
		if (str.string[i].character != a.alphabet.back().character)
		{
			str.string[i] = a.next_char(str.string[i]); // aaazzz -> aabzzz
		}
	}
}

String Generate_nth_lex_str(int n, Alphabet alphabet)
{
	String empty_string, s;
	s = Generate_nth_str_helper(n, alphabet, empty_string);
	return s;
}

bool operator==(Character lhs, Character rhs)
{
	return lhs.character == rhs.character;
}

ostream& operator<<(ostream& out, Character left)
{
	out << left.character;
	return out;
}

ostream& operator<<(ostream& out, String left)
{
	for (int i = 0; i < left.string.size(); i++)
	{
		out << left.string[i];
	}
	return out;
}

int main()
{
	vector<Character> a;
	a.push_back(Character('a'));
	a.push_back(Character('c'));
	a.push_back(Character('c'));
	
	Alphabet alpha(a);

	cout << Generate_nth_lex_str(5, alpha);
	return 1;
}