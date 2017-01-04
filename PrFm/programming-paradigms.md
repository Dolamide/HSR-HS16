# Programming Paradigms

## Imperative

Imperative (befehlend) focuses on *how* it operates

Program = sequence of commands
computation = change of state

Common building blocks

* Assignment (x := x +1)
* Conditional execution (if...then...else)
* Repetition (while...do...)

Origin: "How computers work" (Neumann)

## Declarative

Group - contains *logical* and *functional* programming paradigms

Describes "what" should be done

How is left to the languate's implementation

Programs = Theories of a formal logic
Computation = Decductions

Examples: Spreadsheets, RegEx, SQL, XQuery, Haskell, Prolog..

## Functional Programming

Based on the mathematical function: Each input is
related to exactly one output. For example, $$f(x)$$ only depends on the definition of $$f$$ and the value of the parameter $$x$$

Key Feautres:

* Functions are First-Class Citizens
    * First-Class Citizens = values(normalform), like ints, bools
    * Having better glue, makes Better modularity and reuse (ananlogy charpenter)
* **No mutable State**
    * No imperative control structures (if, for, goto)
    * No assignments
    * this restriction brings (paradoxically) more flexibility

Other features

* Functional programming is a sub group of Declarative Programming.
* Based on Lambda calculus by Alonzo Church
* Expressions are (by default) **side effect free**

Reasons for Functional Programming

* Easier to reason about (especially form mathematically defined problems)
* Easier to get _right_
* Shorter


### The problem with mutable state
Every statement can potentially change the underlying
state of the program. Therefore, the execution is (usually) dependent on the execution of all statements before it.
