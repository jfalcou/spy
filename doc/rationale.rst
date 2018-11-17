Rationale
=========

Version encoding
----------------

Global informations object
--------------------------

Informations about a lot of possible variation points (compiler, compiler version, OS, standard
libraries) have usually been captured as preprocessor macros. Turning those informations into
actual instance required two things:

 - constexpr
 - A language based solution for providing global, constant object in header only libraries.
