Tikili-li-Takili-li-Ptoe
========================

A game less fun than its name, but hopefully a decent GTK+ starting point.

Yes, it's a two-human-player tic-tac-toe game!

Excited?

I didn't think so.  Literally nobody ever demanded such a thing, not even in the days of the Atari 2600 when that might have been better than most of the games on the market.

Still, I wanted to validate that I basically understood [GTK+](http://www.gtk.org/) before trying to apply it to [uManage](https://github.com/jcolag/uManage).  And I'm on a "post everything to GitHub" kick.

Possibly the single most useful feature is that, to my knowledge, no GTK+ tutorial uses [Glade](https://glade.gnome.org/) _and_ grabs individual controls for direct manipulation.

Maybe that's a bad thing, though.  I don't know.

Regardless, if it helps anyone else, it's worth posting.  And _Tikili-li-Takili-li-Ptoe_ is, you have to admit, a pretty great name for the purpose...

I think the P is silent.

Oh, I guess there might be something vaguely clever in checking for a winning condition, maybe.  It took me longer to come up with that than I'd like to admit.

Compiling
---------

For what it's worth, I build _TLTLP_ with:

    gcc tltlp.c -o ttt `pkg-config --cflags --libs gtk+-3.0 appindicator3-0.1` -rdynamic -Wall -Wextra -std=c89 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition

It complains that the event handlers have unused parameters, which is both true and unlikely to change.

In other news, I want to know where `pkg-config` has been all my life...

