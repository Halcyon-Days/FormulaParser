# FormulaParser

This implements a Formula Parser in C++ that when passed a mathematical formula in the format similar to "2.1 * x - 0.1 * y" are variables, returns a Formula Object that has a calculate() method that when given a map which defines those variables, ie. {x->1, y->2}, returns the result


Definitions:

A term represents any variable that can be used in a equation. A term can be: An expression, which combines 2 Terms and links them by an operator, A Tag, which is a variable which can be subsituted by a value, or A number which is a constant.

An Expression will also evaluate its 2 Terms before itself, which allows the order of operations. This means we want to generate all the higher precedence expressions first, so they are operated on first.

The formula parser generates a formula with 2 steps, first parsing through the string and creating 2 lists for all operations and terms and second creating a series of terms that represent the final formula by folding through both lists.

If we take 2.1 * Cuka - 0.1 ^ Moka as an example.
First the 2 lists are generated
TermList = [2.1, Cuka, 0.1, Moka]
ExpressionList = [*, -, ^]

Then the series of terms are created, by iterating over the precedence map and creates expressions in the order of the precendence. The order of creation is symbolic here and will just show the order that expressions will be operated on.
So after the First iteration if precedence 0 = ^, 1 = {*, /}, 2 = {+,-}
TermList = [2.1, Cuka, 0.1^Moka]
ExpressionList = [*, -]
order of creation: 1 = 0.1^Moka 

Second Iteration
TermList = [2.1* Cuka, 0.1^Moka]
ExpressionList = [-]
order of creation: 1 = 0.1^Moka,  2 = 2.1* Cuka,

Third Iteration
TermList = [2.1* Cuka - 0.1^Moka], we return this
order of creation = 1 = 0.1^Moka , 2 = 2.1* Cuka, 3 = result of 1 - result of 2

This way of creating the system makes it extremely open to expansion, as you can add new operations that define a behavior between 2 numbers, like %, and then define its order over others, such as the order of operations in BEDMAS
