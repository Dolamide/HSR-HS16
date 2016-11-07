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

$$(\lambda x.sq \ \ x)(sq \ 5)$$ ➪ $$sq(sq(5))$$
or
$$sq((\lambda y.sq \ y)5)$$ ➪ $$sq(sq(5))$$

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

➪ We currently don't have infix parameters - therefore use prefix form

## Definitions
Definitions are not necessary, but sometimes convenient.

example:

\[
square = \lambda x . \ \cdot\  x\  x
\]

## Currying

The Syntax of λ-Terms allows a single argument. "Currying" allows functions with more than one argument.

A function with several arguments can be thought of as a series of higher-order functions, each of which being unary.

This makes function definitions more concise, modular and reusable - eg. $$addFive = (+\ 5)$$ is much clearer than $$addFive = (\lambda x. +(5, x))$$.
