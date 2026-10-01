"""Cross-check the RPN calculator against an independent reference evaluator.

Generates random expressions in the assignment's input format (tokens separated
by spaces, terminated by '.'), evaluates them with a recursive-descent parser
written here (no shunting-yard, no shared code with the C++ solution) and
compares the final value - or ERROR on division by zero - with the last line
the calculator prints.

Usage: python check_against_reference.py <path-to-rpn-binary> [count] [seed]
"""
import random
import subprocess
import sys


class DivisionByZero(Exception):
    pass


def c_div(a, b):
    if b == 0:
        raise DivisionByZero
    q = abs(a) // abs(b)
    return q if (a >= 0) == (b >= 0) else -q


def evaluate(tokens):
    pos = 0

    def peek():
        return tokens[pos]

    def take(expected=None):
        nonlocal pos
        tok = tokens[pos]
        assert expected is None or tok == expected, (tok, expected)
        pos += 1
        return tok

    def expr():
        value = term()
        while peek() in ("+", "-"):
            op = take()
            rhs = term()
            value = value + rhs if op == "+" else value - rhs
        return value

    def term():
        value = unary()
        while peek() in ("*", "/"):
            op = take()
            rhs = unary()
            value = value * rhs if op == "*" else c_div(value, rhs)
        return value

    def unary():
        if peek() == "N":
            take()
            return -unary()
        return primary()

    def arguments():
        take("(")
        args = [expr()]
        while peek() == ",":
            take()
            args.append(expr())
        take(")")
        return args

    def primary():
        tok = peek()
        if tok.isdigit():
            return int(take())
        if tok == "(":
            take()
            value = expr()
            take(")")
            return value
        take()
        args = arguments()  # all arguments are evaluated, as on the stack machine
        if tok == "IF":
            return args[1] if args[0] > 0 else args[2]
        return min(args) if tok == "MIN" else max(args)

    try:
        value = expr()
        assert peek() == "."
        return str(value)
    except DivisionByZero:
        return "ERROR"


def random_expression(rng, depth=0):
    if depth >= 4 or rng.random() < 0.3:
        return [str(rng.randint(0, 20))]
    kind = rng.random()
    if kind < 0.45:
        op = rng.choice("+-*/")
        return random_expression(rng, depth + 1) + [op] + random_expression(rng, depth + 1)
    if kind < 0.55:
        return ["N"] + random_expression(rng, depth + 1)
    if kind < 0.65:
        return ["("] + random_expression(rng, depth + 1) + [")"]
    name = rng.choice(["MIN", "MAX", "IF"])
    count = 3 if name == "IF" else rng.randint(1, 5)
    tokens = [name, "("]
    for k in range(count):
        if k:
            tokens.append(",")
        tokens += random_expression(rng, depth + 1)
    return tokens + [")"]


def main():
    binary = sys.argv[1]
    count = int(sys.argv[2]) if len(sys.argv) > 2 else 500
    rng = random.Random(int(sys.argv[3]) if len(sys.argv) > 3 else 2024)
    failures = 0
    for _ in range(count):
        tokens = random_expression(rng) + ["."]
        expected = evaluate(tokens)
        line = " ".join(tokens)
        result = subprocess.run([binary], input=f"1\n{line}\n", capture_output=True,
                                text=True, timeout=10)
        lines = [l.strip() for l in result.stdout.splitlines() if l.strip()]
        actual = lines[-1] if lines else "<no output>"
        if actual != expected:
            failures += 1
            if failures <= 5:
                print(f"MISMATCH: {line}\n  expected {expected}, got {actual}")
    print(f"{count - failures}/{count} random expressions match the reference evaluator")
    sys.exit(1 if failures else 0)


if __name__ == "__main__":
    main()
