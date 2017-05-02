# wordgen

A random word generator, given you specify some phonotactic rules! Isn't it beautiful!

wordgen uses a tiny language to cover the phonotactical description of a phonology, and the described model can then be used to randomly generate words and sentences.

## Usage

After compiling with `make`, the executable will be bin/main. Run it then with `bin/main <file name>`. The file will be searched for in the languages/ directory.

The way it is set by default, it parse the file and generate a short text. 

## Syntax

The syntax is pretty rigid now, but I'll change it as soon as I find some spare time.

Every syllable is defined through a sequence of upper case characters, each of them referring to a set of phonemes. Parenthesis can also be used to make enclosing elements optional, appearing 50% of the fime.
An example would be having the sets C = { f, g, th, m, ͼ, ϝr }, V = { a, i, u, υ, η } and F = { n, l, w } and syllables (C)VV and C(C)V(F). This could generate words like faathmυj, ͼηlmiw, gun and ϝrinfguwmal.

Back to serious. The file containing the description must be divided into sections, all of them divided by a line consisting only of `.`. After the last one, a line consisting only of `#`, and all lines after that will be omitted.

The first section contains the sets of glyphs and the single character, upper case name you give it, following the pattern `<Char> = { <list of glyphs, separated with commas> }`.

The second section contains syllable structures, one in each line. It can consist of upper case characters and, optionally, parenthesis to show optionality.
The program does not yet check that the characters you're using here have been previously defined in the first section D= it won't notice untill runtime.

The third section is optional. Here you can specify two values separed by a spacing. They will be stored as the mean and standard deviation values for word length.

After that, as said, optionally a `#` line and comments.

You can also check the files in the languages/ directory to see some examples.

#### Emergent tricks

(C)V(F) (C)V

## Planned enhancements

* Make syntax less rigid:
	* Allow for empty lines.
	* Allow comments anywhere.

* Convert into a more sofisticated typed, interpreted language.

## Catched bugs still to be set free:

* Word and sentence lengths, although sticking to normal distribution, always produces the exact same values.

* Some non deafult word length distributions make the program crash.

* ((A)B)C should be able to generate ABC, BC and C, but now only generates wither ABC or C.
