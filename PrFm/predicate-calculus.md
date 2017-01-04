# First-order Predicate Calculus (FoPC)

Expression
: syntactic construct denoting a math. object such as number, set, function ...
: *expressions can't be proofed - they depend on the input!*
: Only a predicate can be proven ( = expression with input)

Variable
: Identifier / Placeholder: subject to subtstitution

bound variable
: = place holder. It's name has no significance and can be changed.
: Is bound in a certain context:

![](images/bound-variable.png)


free variable
: A variable, that is not bound

## basicFoPCe

basicFoPCe is an extension of PC with a "for all" quantifier, an
equality relation and a an uninterpreded relation symbol:

$$P ::= ... | \forall x.P | E = E | R(\vec{E})$$

$$E ::= x | f(\vec{E})$$

$$\vec{E}$$ = List of Expressions

!!! note

    It's useful to draw an abstract syntax tree!


## FoPCe

![](images/sumary-fopce.png)
: FoPCe in Grün

Note on the Naming of the Rule Schemas
---------------------------------------

eg. ``=goal`` means, that the goal contains an expression with an equal operator.
Can be interpreted as eg. "all expressions are equal to themselfs"

## Excursion: Computing

Logic Programming
: Programs = Rules in predicate logic
: Computation = Proof of predicate

Given the following Graph:

<svg width="134pt" height="260pt" viewBox="0.00 0.00 134.00 260.00" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
<g id="graph1" class="graph" transform="scale(1 1) rotate(0) translate(4 256)">
<title>G</title>
<polygon fill="white" stroke="white" points="-4,5 -4,-256 131,-256 131,5 -4,5"></polygon>
<!-- a -->
<g id="node1" class="node"><title>a</title>
<ellipse fill="none" stroke="black" cx="27" cy="-234" rx="27" ry="18"></ellipse>
<text text-anchor="middle" x="27" y="-229.8" font-family="Times,serif" font-size="14.00">a</text>
</g>
<!-- b -->
<g id="node3" class="node"><title>b</title>
<ellipse fill="none" stroke="black" cx="27" cy="-162" rx="27" ry="18"></ellipse>
<text text-anchor="middle" x="27" y="-157.8" font-family="Times,serif" font-size="14.00">b</text>
</g>
<!-- a&#45;&gt;b -->
<g id="edge2" class="edge"><title>a-&gt;b</title>
<path fill="none" stroke="black" d="M21.1601,-216.411C20.2975,-208.507 20.0481,-198.852 20.4119,-189.935"></path>
<polygon fill="black" stroke="black" points="23.9033,-190.179 21.1206,-179.956 16.9209,-189.683 23.9033,-190.179"></polygon>
</g>
<!-- b&#45;&gt;a -->
<g id="edge4" class="edge"><title>b-&gt;a</title>
<path fill="none" stroke="black" d="M32.8794,-179.956C33.7139,-187.827 33.9485,-197.374 33.5831,-206.187"></path>
<polygon fill="black" stroke="black" points="30.0742,-206.184 32.8399,-216.411 37.0558,-206.691 30.0742,-206.184"></polygon>
</g>
<!-- c -->
<g id="node6" class="node"><title>c</title>
<ellipse fill="none" stroke="black" cx="27" cy="-90" rx="27" ry="18"></ellipse>
<text text-anchor="middle" x="27" y="-85.8" font-family="Times,serif" font-size="14.00">c</text>
</g>
<!-- b&#45;&gt;c -->
<g id="edge6" class="edge"><title>b-&gt;c</title>
<path fill="none" stroke="black" d="M21.1601,-144.411C20.2975,-136.507 20.0481,-126.852 20.4119,-117.935"></path>
<polygon fill="black" stroke="black" points="23.9033,-118.179 21.1206,-107.956 16.9209,-117.683 23.9033,-118.179"></polygon>
</g>
<!-- c&#45;&gt;b -->
<g id="edge8" class="edge"><title>c-&gt;b</title>
<path fill="none" stroke="black" d="M32.8794,-107.956C33.7139,-115.827 33.9485,-125.374 33.5831,-134.187"></path>
<polygon fill="black" stroke="black" points="30.0742,-134.184 32.8399,-144.411 37.0558,-134.691 30.0742,-134.184"></polygon>
</g>
<!-- d -->
<g id="node9" class="node"><title>d</title>
<ellipse fill="none" stroke="black" cx="27" cy="-18" rx="27" ry="18"></ellipse>
<text text-anchor="middle" x="27" y="-13.8" font-family="Times,serif" font-size="14.00">d</text>
</g>
<!-- c&#45;&gt;d -->
<g id="edge10" class="edge"><title>c-&gt;d</title>
<path fill="none" stroke="black" d="M21.1601,-72.411C20.2975,-64.507 20.0481,-54.8518 20.4119,-45.9352"></path>
<polygon fill="black" stroke="black" points="23.9033,-46.1791 21.1206,-35.9562 16.9209,-45.6831 23.9033,-46.1791"></polygon>
</g>
<!-- d&#45;&gt;c -->
<g id="edge12" class="edge"><title>d-&gt;c</title>
<path fill="none" stroke="black" d="M32.8794,-35.9562C33.7139,-43.8272 33.9485,-53.3739 33.5831,-62.1869"></path>
<polygon fill="black" stroke="black" points="30.0742,-62.1835 32.8399,-72.411 37.0558,-62.6911 30.0742,-62.1835"></polygon>
</g>
<!-- p -->
<g id="node11" class="node"><title>p</title>
<ellipse fill="none" stroke="black" cx="99" cy="-234" rx="27" ry="18"></ellipse>
<text text-anchor="middle" x="99" y="-229.8" font-family="Times,serif" font-size="14.00">p</text>
</g>
<!-- q -->
<g id="node13" class="node"><title>q</title>
<ellipse fill="none" stroke="black" cx="99" cy="-162" rx="27" ry="18"></ellipse>
<text text-anchor="middle" x="99" y="-157.8" font-family="Times,serif" font-size="14.00">q</text>
</g>
<!-- p&#45;&gt;q -->
<g id="edge14" class="edge"><title>p-&gt;q</title>
<path fill="none" stroke="black" d="M93.1601,-216.411C92.2975,-208.507 92.0481,-198.852 92.4119,-189.935"></path>
<polygon fill="black" stroke="black" points="95.9033,-190.179 93.1206,-179.956 88.9209,-189.683 95.9033,-190.179"></polygon>
</g>
<!-- q&#45;&gt;p -->
<g id="edge16" class="edge"><title>q-&gt;p</title>
<path fill="none" stroke="black" d="M104.879,-179.956C105.714,-187.827 105.948,-197.374 105.583,-206.187"></path>
<polygon fill="black" stroke="black" points="102.074,-206.184 104.84,-216.411 109.056,-206.691 102.074,-206.184"></polygon>
</g>
</g>
</svg>

Is it possible, to calculate the following questions?

1. Is a reachable from d?
2. Is a *not* reachable from q?
3. Which nodes are reachable from a?

In order to answer these questions, one has to model the problem as a sequent in FoPCe:

Given the following Hypothesis (G)
Reflexive: ∀x. R(x,x )
Symetric: ∀x.∀y. R(x, y) ⇒ R(y, x)
Transitive: ∀x.∀y∀z. R(x, y) ∧ R(y, z) ⇒ R(x, z)

R(a, b), R(b, c), R(c,d) R(p, q)

1. Is a reachable from d? G $$\vdash$$ R(a, d)
2. Is a *not* reachable from q? G $$\vdash$$ ¬ R(a, q)
3. Which nodes are reachable from a? G $$\vdash$$ ∃x.R(a, x)

Now try to proof - if possible, the statement is correct, otherwise not.

## Equational Reasoning

If proofs only involve equality, this is a more compact and better readable
syntax:


![](images/equational-reasoning.png)

## Approach well-formated predicate

1. Expression or Predicate  (eg. Equality is only defined for expressions)
    ``P ::=  ... | ∀x.P | E = E | R(E')``

    ``E ::= x | f(E')``

2. Relation or function symbol
3. Operators OK? (not is unary!)
4. is it ambiguous? - operator precedence OK? (**binding strength**: ``¬``, ``∧``, ``∨``, ``⇒``, ``⇔``)
   -> Can I draw a parse tree
