rc4_tux
=======

This is just a small example what happens if you use one password twice with
a stream cipher (rc4 in this example) without salt. I created this small set
because I saw a nice example example and was unable find the image again.


To create the images yourself just `make` it your own ;-). You need
a C compiler and openssl installed on your system. The images then you will
find under *out*.

What you about to see are 6 Images in 4 steps:

 1. The soure tux

 2. (a/b) The same tux split in two images

 3. (a/b) The split tux images encrypted with rc4 (can be any other stream
    cypher) and *without* salt. Every Image by itself looks random, but even if you
    switch fast between them you can see something.

 4. Can you see the penguin? Is (3a xor 3b). What you're about to see is just
    the same (2a xor 2b).

![example](Tux-rc4.png?raw=true)

I want to thank Dr. Jürgen Koslowski on this place for teaching us the basics
of cryptography.
