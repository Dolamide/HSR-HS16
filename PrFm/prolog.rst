Prolog
======

Use for Prolog ("Programming  with Logic") for..

* ... Applications that would be "trial and error" or search with *backtracking** (eg. Map coloring)
* ... natural language processing, constraint solvers
* ... logical calculator

Prolog is

* declarative
* based on recursion (no for/while) -> recursion
* relations(no functions) - eg woman(mia) <- woman is relation
* unifications

The concept behind it is to first describe the situation (in a knowledge base) and
then ask a query.


Logic Programming Introduction
-------------------------------
**Program** = Predicate calculus
**Computation** = Proof of a sequent

Example: "All humans are mortal. Socrates is human. Therfore, Socrates is mortal."

#. Model as argument as a sequent of FoPCe
    H(x): x is human
    M(x): x is mortal
    s: Sokrates
    ∀x.H(x) => (x), H(s) ⊢  M(s)
#. The anser to the question above can now be calculated by a computer - for example with prolog.

.. code:: prolog

    mortal(X):- human(X).           % All Humans are mortal (rule)
    human(socrates).                % Socrates is human (fact)


    ?- mortal(socrates)             % is socrates mortal (query)
    % yes                             output

Based on the facts abouve, we could also ask other questions.

.. code:: prolog

    human(X).       % all humans
    mortal(X).      % everyone who is mortal
    human(sandro)   % is sandro human

Prolog Basics
--------------

.. image:: images/prolog_terms.png

Atoms
: A sequence of characters of upper-case letters,
: lower-caseletters, digits, or underscore,
: startingwithalowercase letter or anything within single quotes
: Examples: `peter`, `myName`, `burger_king`, 'Vincent', 'Five dollar shake', '@$%'

Numbers
: A sequence of characters of upper-case letters,
: lower-caseletters, digits, or underscore, starting
: with a lowercase letter
: Examples: `X`, `Raphael`, _foo

Complex Terms
: Atoms, numbers and variables are building blocks
: for complex terms. Functor must be an atom
: Examples: `loves(peter, maria)`, `loves(me, Q)`, `loves(me, loves(Q, me))`

Arity
: The number of arguments a complex term has is called its arity
: Examples: `house(messeturm)` arity 1, `loves(me, you)` arity 2

!! warning

    You can define two predicates with the same functor
    but with different arity
    **Prolog treats this as two different predicates!**

    `loves(me, you) % loves/2`

    `loves(me) % loves/1`


Realations
..........

Relational predicates are for example `woman`, `playsAirGuitar` usw.

.. code:: prolog

    woman(mia).                 % relation woman
    woman(jodi).                % relation woman
    woman(yolanda).             % relation woman
    playsAirGuitar(jodi).       % relation playsAirGuitar
    party.                      % relation party

    ?- woman(mia).              % yes
    ?- playsAirGuitar(jody).    % yes
    ?- playsAirGuitar(mia).     % no
    ?- tattoed(jody).           % no or ERROR, depending on the interpreter
    ?- party.                   % yes

Clauses and predicates
......................
Clauses are facts & rules
* Facts: eg. `happy(yolanda).`, `listen2music(mia)`
* Rules (head, body) eg. `playsAirGuitar(yolanda): - listens2music(yolanda).`


Facts, Rules, Head & Body
..........................
.. image:: images/facts_rules.png

And / Or
........

.. code::

    % And - with a comma
    playsAirGuitar(butch):-
        happy(butch),
        listens2music(butch).

    % OR - with a semicolon
    playsAirGuitar(butch):-
        happy(butch);
        listens2music(butch).

Asking Alternatives
...................

.. code:: prolog

    ?-woman(X). % prolog finds ALL the proofs, where

Unification
-------------

Terms unify if they ...

* ... are the same term or #6
* ... contain variables that can be uniformly instantiated with terms in such a way that the resulting terms are equal

Examples:
* `42` and `42` unify
* `42` and `42` unify
* `woman(mia)` and `woman(mia)` unify
* `mia` and `X` unify if mia is substitued with X
* `woman(Z)` and `woman(mia)` unify if mia is substitued with Y
* `loves(mia, X)` and `loves(X, vincent)` can not be unified

Note that Prolog does not use a standard unification algorithm
since it would have serious inpact on the performance,
eg:

.. code:: prolog

    ?-father(X)=X.
    X=father(father(father(father(father(father(father(
    father(father(father(father(father(father(father(
    father(father(father(father(father(father(father(
    father(father(father(father(father(father(father(
    father(father(father(father(father(father(father(
    father(father(father(father(father(father(father(
    father(father(father(father(father(father(
    .............

!! seealso

    Exercises Week 4

Occurs Check
.............

.. code:: prolog

    vertical(line(point(X,Y),point(X,Z))).

    horizontal(line(point(X,Y),point(Z,Y))).

    ?- horizontal(line(point(1,1), point(1, Y))).
    % Y=1;
    % no

!! seealso

    Exercises Week 4


Proof search
------------

.. image:: images/proof_search_tree.png

!! note

    Prollog executes "From top to bottom & left to right"
    This allows us to give priority (which is not possible in *pure* logic)
