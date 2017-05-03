# wordgen

A random word generator, given you specify some phonotactic rules! Isn't it beautiful!

wordgen uses a tiny language to cover the phonotactical description of a phonology, and the described model can then be used to randomly generate words and sentences.

## Usage

After compiling with `make`, the executable will be bin/main. Run it then with `bin/main <file name>`. The specified file will be searched for in the languages/ directory.

The way it is set by default, it parses the file and generates a short, cute, random text. 

## Syntax

The syntax is pretty rigid now, but I'll change it as soon as I find some spare time.

Every syllable is defined through a sequence of upper case characters, each of them referring to a set of phonemes. Parenthesis can also be used to make enclosing elements optional, appearing 50% of the time.
An example would be having the sets C = { f, g, th, m, ͼ, ϝr }, V = { a, i, u, υ, η } and F = { n, l, w } and syllables (C)VV and C(C)V(F). This could generate words like faathmυj, ͼηlmiw, fun and ϝrinfguwmal.

Back to serious. The file containing the description must be divided into sections, all of them separated by a line consisting only of `.`. After the last one, a line consisting only of `#` may be placed, and all lines after that will be omitted.

The first section contains the sets of glyphs and the single character, upper case name you give it, following the pattern `<Char> = { <list of glyphs, separated with commas> }`. One per line.

The second section contains syllable structures, one in each line again. It can consist of upper case characters and, optionally, parenthesis to show optionality.
The program does not yet check that the characters you're using here have been previously defined in the first section D= it won't notice untill runtime.

The third section is optional. Here you can specify, in one line, two values separed by a spacing. They will be stored as the mean and standard deviation values for word length. If this section is not specified, mean and standard deviation will take the values 2 and 1, respectively.

After that, as said, optionally a `#` line and comments after it.

You can also check the files in the languages/ directory to see some examples.

#### Emergent tricks

There is currently no way to directly assign different probabilities to a certain syllable structure, the syllable is always equiprobably chosen from all the existing ones. But a nice way to mischievously simulate it is intentionally adding several times a certain syllable.
For instance, having the sets  above defined, if we want a (C)V(F) structure where F appears very few times, an option would be adding (C)V(F) once and (C)V a couple times.

Another way to simulate it is adding more parenthesis, so that instead of having (C)V(F), with F appearing 50% of the times, you can have (C)V((F)), with F appearing 25% of the times.

Not that classy either way, I know. But it's fun how lawful evil it looks!

## Planned enhancements

* Make syntax less rigid:
	* Allow for empty lines.
	* Allow comments anywhere.

* Convert into a more sofisticated typed, interpreted, gentle-to-use language to be able to cover more restrictions (defining words with syllables instead of having them always randomly chosen, making syllables appear again randomly but only in certain positions inside a word, allow vowel harmony, etc.).

* Transform internally into context-free grammar and apply Early's parsing algorithm to a given text, in order to check if the described phonollogy really applies to all the shown words in the language.

* Way to prohibit the grammar from generating certain types of syllables next to each other.

## Catched bugs still to be set free

* Word and sentence lengths, although sticking to normal distribution, always produces the exact same values.

* Some non deafult word length distributions make the program crash.

* ((A)B)C should be able to generate ABC, BC and C, but now only generates either ABC or C.
