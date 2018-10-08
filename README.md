# SpammerTyper

## Gameplay/Controls

The mechanics behind SpammerTyper are mostly standard typing game mechanics: you're in a fixed position and typeable text is approaching you. In SpammerTyper, these are individual characters rather than words. If you get hit or hit a character that isn't present on screen, you lose HP. The game ends if you lose all your HP. Type the characters to destroy them before they reach you.

The catch: every time you hit a character, the camera zooms in a bit, giving you less time to see and type incoming characters before they reach you. You only need to defend yourself against non-whitespace characters, but you can press spacebar at any time to zoom out.

The other catch: the spawn rate of characters is inversely proportional to the zoom level. If you're zoomed in, you have less time to react to incoming characters, but fewer characters spawn in a given time period. If you're zoomed out, you have more time to react, but you'll have to deal with more characters.

Characters randomly spawn with score or HP bonuses. Red characters give you an HP boost. Green characters give an additional point bonus when typed.

The other other catch: the more HP you have, the faster the newly spawned characters will move. See if you can balance this.

## About

SpammerTyper was created for the [Open Jam 2018](https://itch.io/jam/open-jam-2018). Theme: Spam to win.

## Licensing

Project available under GPLv3. See `LICENSE` for full license text. Orx game engine available under the Zlib license (see [the repository](https://github.com/orx/orx) for details).

Assets available under [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/).
