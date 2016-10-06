Prolog
======

Use for Prolog for..
* .. Applications that would be "trial and error" with backtracking (eg. Map coloring)

Logic Programming Introduction
-------------------------------
**Program** = Predicate calculus
**Computation** = Proof of a sequent

Approach
Example: All humans are mortal. Socrates is human. Therfore, Socrates is mortal.

Model as argument as a sequent of FoPCe

    H(x): x is human
    M(x): x is mortal
    s: Sokrates

    ∀x.H(x) => (x), H(s) ⊢  M(s)

Can now be solved manually or by a computer -> Prolog!

Prolog Introduction
--------------------

Hyoptheses = **Knowledgebase** in Prolog

Knowledge base consists of
* Rules: ≠ proof rule!(predicate)
* Facts is a simple form of a Rule (predicate)

example:

.. code:: prolog

    mortal(X):- human(X).           % All Humans are mortal (rule)
    human(socrates).                % Socrates is human (fact)


    ?- mortal(socrates)             % is socrates mortal (query)
    % yes                             output

Syntax note: **All Quantifications** are impicit when written **in capitals** -
everything else in lowercase.

Implication is "reversed": `mortal(X):- human(X).`: **"implied by"**
"For all X: x is mortal if x is human"

Program and query are separated.

Example Queries would be:

.. code:: prolog

    human(X). // all humans
    mortal(X). //everyone who is mortal
    human(sandro) // is sandro human
