Tikili-li-Takili-li-Ptoe
========================

A game less fun than its name, but hopefully a decent GTK+ starting point.

Yes, it's a two-human-player tic-tac-toe game!

Excited?

I didn't think so.  Literally nobody ever demanded such a thing, not even in the days of the Atari 2600 when that might have been better than most of the games on the market.

Still, I wanted to validate that I basically understood [GTK+](http://www.gtk.org/) before trying to apply it to [uManage](https://github.com/jcolag/uManage).  And I'm on a "post everything to GitHub" kick.

Possibly the single most useful feature is that, to my knowledge, no GTK+ tutorial uses [Glade](https://glade.gnome.org/) _and_ grabs individual controls for direct manipulation.

Maybe that's a bad thing, though.  I don't know.

Regardless, if it helps anyone else, it's worth posting.  And Tikili-li-Takili-li-Ptoe is, you have to admit, a pretty great name for the purpose...

I think the P is silent.

Oh, I guess there might be something vaguely clever in checking for a winning condition, maybe.  It took me longer to come up with that than I'd like to admit.

Compiling
---------

After some frustration in manually writing code to connect to Glade, I wrote a "pre-compiler" to generate skeletal code for me.  TlTlP now uses [GladeGlue](https://github.com/jcolag/GladeGlue).  If you compare the current `main()` function with the version in [the previous release](https://github.com/jcolag/Tikili-li-Takili-li-Ptoe/commit/8b9d6332b0066d5ec3f37f88596fbf914be91139), I think you'll agree that loading the cell buttons into the array is less elegant, but it's otherwise worth it, with more-readable code once the one-time-use variables and infrastructure calls are removed.

Beyond that, for what it's worth, I build TlTlP with:

    gcc tltlp.c tltlp_glade.c -o tltlp `pkg-config --cflags --libs gtk+-3.0 appindicator3-0.1` -rdynamic -Wall -Wextra -std=c89 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition

The `tltlp_glade.c` file is generated from _GladeGlue_.

The compiler complains that the event handlers have unused parameters, which is both true and unlikely to change.

In other news, I want to know where `pkg-config` has been all my life...

