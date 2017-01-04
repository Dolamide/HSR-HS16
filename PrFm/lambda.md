# Lambda Calculus

Can be either a predicates $$P$$ or λ-terms $$M$$. Note that λ-terms are declared recursively

\[
\begin{split}
P & \ \ ::= M = M \\
M & \ \ ::= x \ | \ \lambda x.\ M \ |\ M \ M
\end{split}
\]

Since the definition above is ambiguous binding strength is required for evaluation.

\[
\begin{split}
\lambda. M_1 \ M_2 &= \lambda. (M_1 \ M_2) \not =  \lambda. (M_1 ) M_2 \\
M_1 \ M_2 \ M_3 &= (M_1 \ M_2) M_3 \not = M_1 (M_2 \ M_3)
\end{split}
\]

!!! warning

    Think like a compiler when evaluating a term.
    eg. $$k \lambda y.y z$$ is equivalent to $$k (\lambda y.y) z$$ .
    But $$\lambda y.y z$$ is equivalent to $$(\lambda y.(y z)$$.

"Variable" are (as in FoPC) just placeholders - subject to substitution.
Since variables are just placeholders, the following two statements are syntactically identical $$(\lambda y.y) \hat = (\lambda q.q)$$

Lambda is a quantifiers - just like forall or exist.

Examples for valid λ-terms are: $$x$$, $$\lambda x.x$$, $$(\lambda x.x) y$$, $$((\lambda x.x) y) z$$, $$\lambda x.x y z$$

For a proof, all we care about is weather two λ-terms are identical or not - we don't care about and, or exits etc. Therefore, use the shorter equational style!

Lambda calculus and Turing Machines are equivalent.

## How to read it

\[
(\lambda y.\ y) \ a \ b
\]

"The subterm is a function, that takes y and returns y"

"The subterm is the application of the identity function to the variable b"

"The result of the above applied to the variable b"


## Beta Reduction
The Beta Reduction Rule is the only significant rule for lambda calculus (at least in this course...).

\[
\frac{}{H \vdash (\lambda x.\ M)\ N = [x:=N]M }\beta
\]

Which basically means apply the formal parameter in the function definition with the actual values that I have at the point of execution.

It's much easier to apply in the equational style syntax

\[
\begin{align*}
(\lambda y.\ y) \ a \ b && \\
= a \ b && \because \beta
\end{align*}
\]

### Confluence: Execution strategy does not matter

\[
(\lambda x.sq \ x)((\lambda y.sq \ y) 5)
\]

Multiple execution strategies can be used here - but it does not matter since the result remains the same.

$$(\lambda x.sq \ \ x)(sq \ 5)$$ -> $$sq(sq(5))$$
or
$$sq((\lambda y.sq \ y)5)$$ -> $$sq(sq(5))$$

The computation would not be deterministic without this property! (Many programming languages do not have this property and  therefore need to restrict their execution order)

## Computation with the Lambda Calculus

Computation is achieved by repeatedly apply the beta rule until the term is in the *Beta normal form*, which means that no further beta reductions are possible. Every λ-term can only have **zero or one normal form** - which means that not all λ-terms have normal forms!

\[
\begin{split}
&(\lambda x.\ x \ x)(\lambda x.\ x \ x) \\
&=(\lambda x.\ x \ x)(\lambda x.\ x \ x) \because \beta\\
&=(\lambda x.\ x \ x)(\lambda x.\ x \ x) \because \beta\\
&= ...
\end{split}
\]

| Math Syntax | λ-Term Syntax |
|-------------|---------------|
| f(x)        | f x           |
| sin(x)      | sin x         |
| f(g(x))     | f (g x)       |
| f(x, y)     | f x y         |
| x + y       | + x y         |
| $$x^y$$     | power x y     |

-> We currently don't have infix parameters - therefore use prefix form


## Currying

The Syntax of λ-Terms allows a single argument. "Currying" allows functions with more than one argument.

A function with several arguments can be thought of as a series of higher-order functions, each of which being unary.

This makes function definitions more concise, modular and reusable - eg. $$addFive = (+\ 5)$$ is much clearer than $$addFive = (\lambda x. +(5, x))$$.

## Definitions & $\delta$-Reduction
Definitions are not necessary, but sometimes convenient.

example:

\[
square = \lambda x . \ \cdot\  x\  x
\]

$\delta$-Reduction is the substitution of a defined symbol with its definition.

## Higher-Order Functions

Higher-Order Functions are functions that accept a function as input and/or return a function as output.

They require no special treatment since functions are first-class citizens in lambda calculus.

## Evaluation Strategies
Lambda calculus does not place any constraints on the order, in which redexes are reduced. However, the evaluation strategy is crucial in lenght of derivation and especially their _termination_.

redex
: Reducable Expression - every $\delta$ and β reducable subterm.

### Innermost-first
The innermost redex is reduced first.

Analogue to _pass by value_ - terms are fully evaluated. This means, that endless loops are more likely in comparison to outermost-first.

Function arguments are reduced exactly once.

_Usually_, innermost-first results in a shorter derivation.

Tiebreaker: If there are more than one innermost redex, the leftmost-innermost redex is reduced first. In other words: This is the case if multiple redexes are not contained in each other.


### Outermost-first
The outermost redex is reduced first.

Analogue to _pass by name_ - terms are evaluated when needed. Endless loops can be avoided.

Function arguments are reduced as often as they are needed. To improve performance, caching can be used (Lazy evaluation).

In case an **normal form** exist, outermost-first will find it.

Tiebreaker:  If there are more than one outermost redex, the leftmost-innermost redex is reduced first.

### Non-Terminating Evaluation

Sometimes, one evaluation strategy can fail, when another works.

\[
\begin{align}
L &= \lambda x.\lambda y. \ y \\
\omega &= \lambda x . \ x \ x \\
\Omega &=  \omega \ \omega
\end{align}
\]

Here, the innermost-first strategy results (because _pass by value_) does not find a normal form.

\[
\begin{align}
&L\ \Omega \\
&=(\lambda x.\lambda y.\ y)\ \Omega & \because \delta\\
&=(\lambda x.\lambda y.\ y)\ (\omega\ \omega) & \because \delta\\
&=(\lambda x.\lambda y.\ y)\ ((\lambda x.\ x \ x)\ \omega) & \because \delta\\
&=(\lambda x.\lambda y.\ y)\ ((\lambda x.\ x \ x)\ (\lambda x.\ x \ x)) & \because \beta\\
&=(\lambda x.\lambda y.\ y)\ ((\lambda x.\ x \ x)\ (\lambda x.\ x \ x)) & \because \beta\\
&=(\lambda x.\lambda y.\ y)\ ((\lambda x.\ x \ x)\ (\lambda x.\ x \ x)) & \because \beta\\
&\vdots
\end{align}
\]

The outermost-first strategy however (because _pass by name_) does find a normal form.

\[
\begin{align}
&L\ \Omega \\
&=(\lambda x.\lambda y.\ y)\ \Omega & \because \delta\\
&=\lambda y.\ y &\because \beta\\
\end{align}
\]

## Encoding
Since pure lambda calculus does neither have primitive data types, boolean algebra nor arithmetic operations. However, all of it can be encoded in lambda calculus.

!!! note

    It's not important to understand why and how the encoding rules work but it it's important to be able to apply them.

\[
\begin{align}
(\lor \ \top \ \bot) = \top \\
\\
(\underline{\lor} \ \top \ \bot) \\
&= \underline{(\lambda p. \lambda q.\ p \ p\ q)\  \top} \ \bot & \because \delta \\
&= \underline{(\lambda q.\ \top \ \top\ q) \ \bot} & \because \beta \\
&= \underline{\top} \top \bot & \because \beta \\
&= \underline{(\lambda x.\lambda y.\ x)\ \top} \bot & \because \delta \\
&= \underline{(\lambda y.\ \top)\ \bot} & \because \beta \\
&= \top & \because \beta
\end{align}
\]
