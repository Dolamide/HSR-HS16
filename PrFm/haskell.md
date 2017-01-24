# Haskell

## Haskell overview

In contrast to math, function application in Haskell is is denoted using space.

Custom functions are defined within a _script_ - a simple text file with the `.hs` extension.


Haskell comes with many function in the standard library (*standard prelude*) - many that we already know from prolog.

* `head [1, 2, 3, 4, 5]` - `1`
* `tail [1, 2, 3, 4, 5]` - `[2, 3, 4, 5]`
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

    `f a b + c * d` -> `f(a b) + c d`

    `f a + b` -> `(f a) + b`


Any functions with two arguments can be written bewtwen its arguments by enclosuing the name of the function in singl eback quotes. This can improve readability

```haskell
average ns = sum ns `div` lenght ns
-- equivalent to
average ns = div (sum ns) (lenght ns)

```

## Naming conventions

* functions and arguments must be lowercase
* list arguments have an s suffix (by convention)
    * nss would be a list of lists

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
while(n > 0){
    result = result*n;
    n = n-1;
}
```

Functional version (recursive definition)

```haskell
fact 0 = 1
fact n = n * (fact n - 1)
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

## Types

type
: Collection of related values

Basic Types

* `Bool` - contains `True` and `False`
* `Char` - `a`, `b`, ...
* `String` (which is actually a list of char `:type "foo"` -> `"foo" :: [Char]`)
* `Int` - fixed size
* `Integer` - No fixed size
* `Float`
* `Double`

Types can be set manually using two colons: `1 :: Float`

Haskell (automatically) determines the Types at compile time using **Type inference** - which makes Haskell type safe (no type errors at runtime). This means, that a function must allways return values of the same type (eg. not 1 and False)

Examples

* `Bool` contains `True` and `False`
* `Bool -> Bool` Contains all Functions, that map Bool-Arguments to a resulting Bool (eg. `not`)

### Lists in Haskell

Sequence of elements **of the same type**. The type only defines the type and nothing else (eg. lenght). Lists don't have to be finite.

Examples

* `[False, True, False] :: [Bool]`
* `['a', 'n', 'q'] :: [Char]`
* `["Foo", "Baa"] :: [[Char]]` (or `:: [String]`)

### Tuples

Tuples are a **finite** sequence of components of **possibly different types**. The type conveys (in contrast to List) the arity of the tuple.

Tupels of size 1 are not permitted - But 0, 2, 3 ... n.

Examples

* `(False, True) :: (Bool, Bool)`
* `('a', True, "Haha") :: (Char, Bool, [Char])`

### Function types
A function is a **mapping** from agruments of some type to results of possibly another type.

Examples

* `even :: Int -> Bool`
* `add :: (Int, Int) -> Int`

Note, that the `:type` command in GHCi will return the Curryed version of it - eg: `:type (+)` -> `(+) :: Num a => a -> a -> a` Which means that it takes two arguments (one at a time) of type `a` and returns a result of type `a` as well.

Currying enables _partially applying a curried function_, for example `double = (* 2)`, `double 15`.

```haskell
add x y =x + y
-- means
add = \ x -> (\ y -> x + y)
```

!!! note

    To avoid excess of parentheses when using curried functions, the following conventions are adopted:

    * Arrows `->` are **right associative** (eg. `int->int->int->int` = `int->(int->(int->int))`)
    * Function applications are **left associative** (eg. `add x y z` = `((add x)y)z`)


**It is good practice to define the type of a function prior to starting to define the function itself**

### Polymorphic Functions

Polymorphic Functions are Type Variables where the type is substituted wit a a placeholder. These type parameters must be lowercase and are usually a single character. Example `length :: [a] -> Int` or `zip :: [a] => [b] -> [(a,b)]`

### Overloaded Functions

The `+` Method should be applicable for `Int`s as well as `Float`s etc. This can be achived using *type classes*. Type classes are similar to interfaces.

To enable overloaded functions, polymorphic functions can be applyed with **class constraints**.

`(+) Num a => a -> a -> a`

Common type classes are `Num` (numeric types), `Eq` (equality types, eg `==`), `Ord` (ordered types, eg. `>` or `<`)

!!! todo

    Duck typing theorie lesen (Bevavuiral Polimorphism)
    Type hints

## Defining Functions

* Use other Functions - eg. ```even n = n `mod` 2 == 0```
* Conditional Expressions - Like "Java"
    * Exactly: ONE if and ONE else
    * May be nested

    ```haskell
    signum n = if n < 0 then -1 else
                    if n == 0 then 0
                    else 1
    ```

* Guarded Equations
    * Mathematical intuition
    * `otherwise` is synonym for `True`
    * The Order, in which the Guards are defined is crucally important!
    * The symbol `|` is read as _"such that"_
    * other is not required but pretty and readable

    ```haskell
    signum n | n < 0     = -1
             | n == 0    = 0
             | otheriwse = 1
    ```

* Pattern Matching
    * eg. not - well readable (if possible)
    * order should NOT matter
    * Can only bind a variable ONCE! (eg. `b&& b=b` is invalid)

    ```haskell
    True && True = True
    True && False = False
    False && True = False
    False && False = False
    -- simpler with wildcard patterns
    True && True = True
    _ && _ = False
    ```

* List Patterns
    * Internally, every non-empty list is constructed by repeated use of the `cons` operator
    * `x : xs` matches only non-empty lists!

    ```haskell
    -- Partical use of cons
    head (x : _) = x
    tail (_ : xs) = xs --

    -- Syntactic Shugar
    [1,2,3,4]
    -- is equal to
    1 : (2 : (3 : (4 : []))).
    ```

* Lambda Expressions
    * void naming functions that are only referenced once
    * return functions as results

    ```haskell
    > (\x -> x + x) 2
    4
    ```

* Operator Sections
    * Convert infix operator into curried function

    ```haskell
    plusone = (1+)
    divideByTwo = (/2)
    plusone 2
    ```

## List Comprehension

Set Comprehensions are common in mathematics. Haskell knows a similar notation. It's the same concept as in Python but with different syntax.

List Comprehensions are a very elegant way to perform iteration in the declarative style.

```haskell
-- math: {x^2 | x \in {1...5}}
[x^2 | x <- [1..5]]
-- Result: [1,4,9,16,25]

[(x, y) | x <- [1,2,3], y <- [4, 5]]
-- Result: [(1,4),(1,5),(2,4),(2,5),(3,4),(3,5)]
[(x, y) | y <- [4, 5], x <- [1,2,3]]
-- Result: [(1,4),(2,4),(3,4),(1,5),(2,5),(3,5)]
[(x,y) |  x <- [1..3], y <- [x..3]]
-- Result: [(1,1),(1,2),(1,3),(2,2),(2,3),(3,3)]
concat xss = [x | xs <- xss, x <- xs]

-- using guards
factors n = [x | x <- [1..n], n `mod` x == 0]
-- prime n = factors n == [1, n]
-- prime 15

```

* `x <- [1..5]` is a **Generator**.
* Comprehensions can have multiple generators, separated by commas.
    * The **order** is important (like nested loops)
    * generators can depend on the variables that are introduced by earlier generators
* guards restrict the values (equivalent to `if` in python list comprehensions)

#### The zip function

Zip generates a list of pairs for two given lists.

```haskell
zip [1,2,3] ['a', 'b', 'c']
-- Result: zip [1,2,3] ['a', 'b', 'c']
positions x xs = [i | (k, i) <- zip xs [0 ..], k == x]
```

!!! note

    Strings are nothing else than a list of Chars. Therefore, operations such as `zip`, `take` or `lenght` work on strings as well.

    -> "String comprehensions"

## Recursion in Haskell

Recursion is pretty straight forward - as we know it from the non-functional World as well as from Prolog.

```haskell
-- Simple factorial recursive definition
fac :: Int -> Int
fac 0 = 1 -- base case
fac n = n * fac (n-1) -- recursive case

-- Lenght - analog zu Prolog
length :: [a] -> Int
length []= 0
length (_:xs) = 1 + length xs

-- Reverse - analog zu Prolog
reverse :: [a] -> [a]
reverse []= []
reverse (x:xs) = reverse xs ++ [x] -- Append operator

-- zip
zip :: [a] -> [b] -> [(a,b)]
zip [] _ = []
zip _ [] = []
zip (x:xs) (y:ys) = (x, y) : zip xs ys

-- quicksort
qsort :: Ord a => [a] -> [a]
qsort [] = []
qsort (x:xs) = qsort smaller ++ [x] ++ qsort larger
                where
                    smaller = [a | a <- xs, a <=x ]
                    larger = [b | b <- xs, b > x]
```

### Recipe

1. Define the type (eg. `product :: [Int] -> Int`)
2. Enumerate the cases (eg. `product [] = `, `product(n:ns) = `)
3. Define the simple cases (`product [] = 1`)
4. Define the other cases (eg. `product (n:ns) = n * product ns`)
5. Generalise and simplify

Alternative

1. Write down type signature
2. Choose parameter(s) over which to perform recursion
3. Write down case distinctions on the left side
4. For each recursive case, write the recursion
5. Complete right side of the definition
6. Check the inferred types agrees with the definition.

## Higher-Order Functions in Haskell

Common programming patterns can be encapsulated within the language itself.

> "A function that takes a fuction as an argument or returns a function as a result is called a higher-order function. In (Haskell) practice, the term is often used when taking functions as arguments." - <cite>Programming in Haskell by Graham Hutton</cite>


```haskell
-- Map: Apply the given method to all elements in the list.
map :: ( a -> b) -> [a] -> [b]
map f [] = []
map f (x:xs) = f x : map f xs

-- or use list comprehension for declaration
-- not recommended for reasoning purpose
map f xs = [f x | x <- xs]


filter (a -> Bool) -> [a] -> [a]
filter p [] = []
filter p (x:xs) | p x       = x : filter p xs
                | otherwise = filter p xs

-- or use list comprehension for declaration
-- not recommended for reasoning purpose
filter p xs = [x | x <- xs, p x]


-- The (.) Function returns a composition of
-- two functions. eg. odd = not . even
(.) :: (b -> c) -> (a -> b) -> (a -> c)
f . g = \ x -> f (g x)

-- True, if p is true for all elements of xs
all :: (a -> Bool) -> [a] -> Bool
all p xs = and [p x | x <- xs]

-- True, if any of the elements of xs is true
any :: (a -> Bool) -> [a] -> Bool
any p xs = or [p x | x <- xs]

-- Select elements from a list while the given
-- predicate returns true
-- eg. takeWhile (\x -> (x > 0)) [ 3,2,1,0,-1] -> [3,2,1]
takeWhile :: (a -> Bool) -> [a] -> [a]
takeWhile p [] = []
takeWhile p (x : xs) | p x       = x : takeWhile p xs
                     | otherwise = []

-- Drops elements elements from a list while the given
-- predicate returns true
-- eg. drowWhile (\x -> (x > 0)) [ 3,2,1,0,-1] -> [0, -1]

drowWhile :: (a -> Bool) -> [a] -> [a]
drowWhile p [] = []
drowWhile p (x : xs) | p x       = dropWhile p xs
                     | otherwise = x : xs
```

### foldr / foldl (=reduce)
The foldr function is a simple pattern of recursion on lists. Very useful, because if the performace of this pattern can be improved, all functions based on it get faster as well.

```haskell
f [] = v
f (x:xs) = x # f xs
-- Where # stands for any function

-- example usage of this pattern
sum [] = 0
sum (x:xs) = x + sum xs

or [] = False
or (x:xs) = x || or xs
```

The foldr (short for fold right) encapsulates this pattern of recursion:

```haskell
foldr :: (a -> b -> b) -> b -> [a] -> b
foldr f v [] = v
foldr f v (x:xs) = f x (foldr f v xs)

sum = foldr (+) 0
or = foldr (||) False
lenght = foldr (\ _ n -> 1 + n) 0
-- Note, the lambda function is called with 2 parameters: first, the current value and second, the result of the recursion.

reverse = foldr snoc []
-- snoc is cons backwards
-- ...
```

## Declaring Types & Classes
* Names of types **must always** start with an **upper case letter**.

### Synonyms (`type`)
Synonym types are new names for existing types, for example

```haskell
type String = [Char]
```

* Synonym types are just a tool to improve readability.
* Synonym type declarations can have parameters

    ```haskell
    type Pair a = (a, a)
    ```

* Synonym type delcarations can be transitive but **NOT** recursive

    ```haskell
    -- Transitive delcaration - works just fine
    type Pos = (Int, Int)
    type Trans = Pos -> Pos

    -- recursive declaration - does not work!
    type Tree = (Int, [Tree])
    ```

### Data Declarations

completely new type
can be

eg. `data Bool = False | True` ("Bool is a new type, with two new values False and True.")

New values (False and True) of the type are called *constructors*

Constructors must also start with an uppercase letter
Same constructor name can not be used in more than one type.

The definitions so far is not more than an enum.

The Constructors in data declaration can have parameters - which are basically functions as well

```haskell
data Shape = Circle Float | Rect Float Float
-- > :type Circle
-- Circle :: Float -> Shape
-- > :type Rect
-- Circle :: Float -> Float -> Shape

-- example usage
square :: Float -> Shape
square n = Rect n n
```

Data Declarations can be have parameters

```haskell
-- A data type like javas Optional class
data Optional a = Nothing | Exactly a

-- example usage
safediv :: int -> int -> Optional Int
safediv _ 0 = Nothing
safediv m n = Exactly (m `div` n)
```


### Recursive Types

```haskell
-- Example "Natural numbers"
data Nat = Zero | Suc Nat
-- eg. Suc(Suc(Suc Zero)) represents 3
```

### Arithmetic Expressions

?!

### Binary Trees (Flatten = inorder traversal)

```
```

```haskell
data Tree a = Leaf a | Node (Tree a) a (Tree a)
-- Exaple
--      5
--    /   \
--   3     7
--  / \   / \
-- 1   4  6  9
t :: Tree Int
t = Node (Node (Leaf 1) 3 (Leaf 4)) 5 (Node (Leaf 6) 7 (Leaf 9))
```

This new data structure can now easily be queried

```haskell
-- Check if a value is in the tree
occurs :: Ord a => a -> Tree a -> Bool
occurs x (Leaf y) = x == y
occurs x (Node l y r) = x == y || occurs x l || occurs x r

-- convert the tree into a list - with the example
-- above [1, 3, 4, 5, 6, 7, 9]
flatten :: Tree a -> [a]
flatten (Leaf x) = [x]
flatten (Node l x r) = flatten l ++ [x] ++ flatten r
```

## Polymorphism

* **Ad-hoc Polymorphism** -> Haskell uses type  classes (Eq, Num, etc) - is similar to interfaces in Java.
* Parametric Polymorphim
* Subtype Polymorphim (not supported in most functional languages)

Classes - similar to an interface in Java.

```haskell
class Eq a where
    (==), (/=) :: a -> a -> Bool

    x /= y = not (x == y)
```

"For a type to be an instalce of the class `Eq`, it must support equality and inequality operators of the specified types."
A default definiton for unequality is already provided - therefore, a type requires only a `==` operator.

Here is an example instantiation

```haskell
instance Eq Bool where
    Fals == False = True
    True == True  = True
    _    == _     = False
```
This does not work for synonym types!


Can be simplified using the `deriving` Mechanism.

```haskell
data Bool = False | True
            deriving (Eq, Ord, Show, Read)
```
