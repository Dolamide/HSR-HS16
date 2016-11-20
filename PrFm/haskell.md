# Haskell

## Haskell overview

In contrast to math, function application in Haskell is is denoted using space.

Custom functions are defined within a _script_ - a simple text file with the `.hs` extension.


Haskell comes with many function in the standard library (*standard prelude*) - many that we already know from prolog.

* `head [1, 2, 3, 4, 5]` - `1`
* `head [1, 2, 3, 4, 5]` - `[2, 3, 4, 5]`
* `take 3 [1, 2, 3, 4, 5]` - `[1, 2, 3]`
* `drop 3 [1, 2, 3, 4, 5]` - `[4, 5]`
* `lenght [1, 2, 3, 4, 5]` - `5`
* `sum [1, 2, 3, 4, 5]` - `15`
* `product [1, 2, 3, 4, 5]` - `120`
* `reverse [1, 2, 3, 4, 5]` - `[5, 4, 3, 2, 1]`
* Append two lists `[1, 2, 3] ++ [4, 5]`
* Select the nth element of a list `[1, 2, 3, 4, 5] !! 2` - `3`

!!! warning

    * function application is denoted using space
    * function appliaction binds stronger than all other operators
    `f a b + c * d` ➪ `f(a b) + c d`
    `f a + b` ➪ `(f a) + b`


Any functions with two arguments can be written bewtwen its arguments by enclosuing the name of the function in singl eback quotes. This can improve readability

```haskell
average ns = sum ns `div` lenght ns
-- equivalent to
average ns = div (sum ns) (lenght ns)

```

## Naming conventions

* functions and arguments must be lowercase
* list arguments have an s suffix (by convention)

## GHCi
GHC = Glasgow Haskell compiler.

```bash
$ ghci
$ ghci my_script.hs
```

```haskell
-- Load a file
:l "demo.hs"
:load "demo.hs"

-- reload the last loaded file (here: demo.hs)
:reload
:r

-- set and open editor
: set editor name
: edit filename.hs
: edit

-- show type of expr
: type expr

-- other
: ?
: quit
```

## Data Structure



List can be defined as $$Lst := Nil\; |\; const\; e \;Lst$$, where $$e$$ is the head and the second $$Lst$$ the tail.


Definition of an abstract data type


```haskell
data lst a = Nil |  Cons a (Lst a)
    derivating (Show)

l1 = Cons 'a' (Cons 'b' Nil)
len Nil = 0
len (Cons x xs) = 1 + (len xs)
```


However, lists can be used much simpler using eg. `[1..10]`

!!! note

    Haskell is strongly typed! (uses prolog-style proof to get the type) - use `:type "abc"` to get the type of sth.


## Demos

!!! seealso

    Code Samples in the `demo` directory.

### Demo Factorial

\[
 n!={\begin{cases}1&{\text{if }}n=0,\\(n-1)!\times n&{\text{if }}n>0\end{cases}}.
\]

Imperative version (pseudo code)

```
n = input
result = 1;
```c++
while(n > 0){
    result = result*n;
    n = n-1;
}
```

Functional version (recursive definition)

```haskell
fact 0 = 1;
fact n = n * (fact n - 1);
```

Functional is much more readable, since it is basically equivalent to the mathematical definition.

Because there are no side effects, the functional version can be optimized and parallelized by the compiler. This can be seen, when the above program is executed for a huge number.


### Demo Fibonacci

Definition

\[
F_{1}=1,\\
F_{2}=1,\\
F_{n}=F_{n-1}+F_{n-2}
\]


functional version (again, based on recursion)

```haskell
fib 0 = 1
fib 1 = 1
fib (n) = (fib (n-1)) + (fib (n-2))
```

Example usage

```haskell
-- first 12 elements of the fibonacci series
fibsN n = map fib [0..n]
fibsN 12
-- Output: [1,1,2,3,5,8,13,21,34,55,89,144,233]

{- or get ALL the fibonacci numbres using an
infinite implementation -}
fibs = map fib [0..]
-- Output: [1,1,2,3,5,8,13,21,34,55,89,144,233, ...

-- thanks to lazy loading & take function, take the first n with fibs
take 12 fibs
-- Output: [1,1,2,3,5,8,13,21,34,55,89,144,233]
```

The compiler can use tail recursion or use dynamic programming for optimizing.
