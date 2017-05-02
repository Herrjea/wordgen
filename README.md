# wordgen

A random word generator, given you specify some phonotactic rules! Isn't it beautiful!

wordgen uses a tiny language to cover the phonotactical description of a phonology, and the described model can then be used to randomly generate words and sentences.

## Usage



## Syntax



### Emergent tricks

(C)V(F) (C)V

## Planned enhancements

	Make syntax less rigid:
		Allow for empty lines.
		Allow comments anywhere.

### Catched bugs still to be set free:

	* Word and sentence lengths, although sticking to normal distribution, always produces the exact same values.

	* ((A)B)C should be able to generate ABC, BC and C, but now only generates wither ABC or C.
