# About Klavier

[Klavier](http://richdark.github.io/klavier) is a simple desktop application that makes typing French accents very easy, no matter what common (latin based) keyboard layout you use. It was inspired by a program called [Tajpi](http://www.zz9pza.net/tajpi/en/), which serves for a similar purpose regarding Esperanto language. Similarly as Tajpi, Klavier makes no changes to a system, it just sits in the background and modifies accents when a hotkey is pressed.

## Usage

Actual accents are produced by typing a base letter, e.g. "a" and looping between available diacritic marks by pressing the hotkey repeatedly. Typing an "a" letter and then immediately pressing the hotkey will therefore replace "a" with an "à". Another hotkey press will change "à" to "â", then "æ" and then "a" again. The very same effect is applicable for all other similar letters, like e, i, c and so on.

The hotkey can be mapped to either `Insert` key or `K` key. K is very rarely used in French, mainly in foreignwords, so if `Insert` key is not a possible choice, it can be replaced with the `K` key easily.

## Additional notes

I've made this simple application for my own use and in my free time, since I hate switching between software keyboards. I share Klavier with ther rest of the world because I know there may be a lot of people with similar dislike. Because of that (and although I will surely be happy to hear some feedback and maybe even ideas for an improvement), I cannot guarantee anything besides that I will reply to and take every suggestion into account.

## Requirements

Klavier was written to run under Microsoft Windows, it uses some Windows-specific functions and mechanisms, especially WinAPI keyboard hooks. Because of that, Klavier in its current state is not platform independent. Right now, I have no plans of porting Klavier to Linux or OS X. If you are interested to do so, feel free to fork the repository.

# Download

Go to the [Klavier website](http://richdark.github.io/klavier) in order to download the latest version. Both portable executable and installer containing the necessary Visual C++ Redistributable Package are available.

# Licensing

I share all my code under MIT license. See [license.txt](license.txt) for more information.

## Third party acknowledgement

Klavier was developed using the fantastic [Qt](https://www.qt.io) framework. Besides that, the application makes use of the third-party libraries listed below:

- [JsonCpp](https://github.com/open-source-parsers/jsoncpp) (storing and retrieving user settings in a JSON format).