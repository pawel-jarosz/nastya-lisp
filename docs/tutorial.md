# Nastya Lisp - language tutorial by examples

## Atomic types

```lisp
? | #true
  | Boolean => #true
? | #false
  | Boolean => #false
? | "abc"
  | String => abc
? | 1
  | Integer => 1
? | 1.3
  | Floating => 1.3
? | dummy_label
  | Label => dummy_label
```

## Lists

Lists are hetereogenous structure which means that it is an ordered set of data in different types.
They are presented in following format:

``` lisp
(1 #true 3.14)
```

means a list with following elements - first element is element 1, second boolean #true and third 3.14.

Lists are real fundament of this language all expressions in this language are atoms or they are a list.
Basic command looks like similar manner:

``` lisp
(command_label arg1 arg2 arg3 ... argN)
```

***Nastya Lisp*** implements following operations on a lists:

* `Quote` - returns argument without computing expressions value

``` lisp
? | (Quote (1 "abc" 2.3))
  | List => (1 "abc" 2.3) // lists are heterogenous structure
```

You can use **'** character as a syntactic sugar because using `Quote` can be inconvinient in longer expressions like:

``` lisp
? | '(label 1 2 (#true 3.14 ("string")))
  | List => (label 1 2 (#true 3.14 ("string")))
```

* `Head` - returns the first element of a list

``` lisp
? | (Head '(1 2 3))
  | Integer => 1
```

* `Tail` - returns list without a first element,

``` lisp
? | (Tail '(1 2 3))
  | List => (2 3)
```

In a future there will be implemented functions

* `Empty` - returns if a list is empty
* `Length` - returns a number of list elements

## Arithmetic
To be done soon...

## Comparisions

Comparisions can be performed on a strings and numbers. There is available following *true/false* commands:

* `Lower`
* `LowerOrEqual`
* `Equal`
* `GreaterOrEqual`
* `Greater`

They can be used in a following manner:

``` lisp
(comparing_command a b)
```

Command `Greater` is an equivalent of mathematic expression `a > b`, similarily `GreaterOrEqual` is `a >= b` etc.

### Example

``` lisp
? | (Greater 1 2)
  | Boolean => #false
```

There is available one more useful command:

* `Compare` - returns type of relation


    1 - if the first value is greater than second,

    0 - if two values are equal

    -1 - if the first value is lower than second

### Example

```lisp
? | (Compare 1 2)
  | Integer => -1
```

## Conditionals

There is available two condition methods:

* `If` command has following command

```lisp
? | (If boolean_expression true_result false_result)
```

where boolean expression is an expression which computes to boolean value. If expression
reduces to `#true` then `If` expression returns `true_result` otherwise returns `false_result`.

### Example

``` lisp
? | (If #true 1 2)
  | Integer => 1
? | (If #false 1 2)
  | Integer => 2
? | (If (Greater 1 2) #true #false)
  | Boolean => #false
```

* `Cond` - receives list of condition an return values


``` lisp
? | (Cond (condition1 value1) (condition2 value2) ... (conditionN valueN) (Else otherwise_value))
```

Conditions are an expression reductible to boolean value. If `condition1` is true then expression value is `value1`,
than there is checked in similar manner `condition2`, `condition3`... If all conditions failed expression value is
value in `Else` block - in our sample it is `otherwise_value`. `Else` value is not an obligatory block.

``` lisp
? | (Cond ((Greater 1 2) 1) ((GreaterOrEqual 1 2) 2) ((Equal 1 2) 3) (Else 4))                       
  | Integer => 4
? | (Cond ((Greater 1 2) 1) ((Greater 2 1) 2))
  | Integer => 2
```

## `Define` command

`Define` keyword register named constant value on pseudo-heap.

``` lisp

? | (Define Pi 3.14)
  | Label => Pi
? | Pi
  | Floating => 3.14
```

## `Let...In...` command

Syntax `Let...In...` pushes a frame on the pseudo-stack and registers constants given in section `Let`,
after registration computes formula in section `In`. The last step is remove top from the pseudo-stack.

``` lisp
? | (Define isEmpty (Lambda (list) (If (Equal list '()) #true #false)))
  | Floating => 3.14
```

## Lambda expression

`Lambda` expression has following structure:

``` lisp
(Lambda (argument_name1 argument_name2 ... argument_nameN) (computable_expression))
```

There is an example:
```lisp
? | (Define IsEmpty (Lambda (list) (If (Equal list '()) #true #false)))
  | Label => IsEmpty
? | (IsEmpty '())
  | Boolean => #true
? | (IsEmpty '(123))
  | Boolean => #false
```

## Terminal command

Command line interface implements additional module which implements functionalities to perform by user on an interface.
There is available following command:

* `Exit-Console` - closing terminal.

```lisp
(Exit-Console)

