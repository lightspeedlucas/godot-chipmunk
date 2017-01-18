#!/usr/bin/python
import re
import sys

# build a list of ignored functions
ignoredPatterns = ["_init$", "_alloc$", "_destroy$", "_user_data$", "_each_", "_func$", "_debug_", "^space_get_static_body$"]
ignoredPatterns = [re.compile(p) for p in ignoredPatterns]

# type conversion map
datatypes = {
    "cpFloat": "float",
    "cpBool": "bool",
    "cpCollisionType": "int",
    "cpGroup": "int",
    "cpBitmask": "int",
    "cpVect": "Vector2",
    "cpTransform": "Matrix32",
    "cpBodyType": "int",
    "int": "int",
    "cpTimestamp": "int",
    "cpBB": "Rect2"
}

resourcetypes = ["cpBody", "cpSpace", "cpShape", "cpConstraint"]

mathTypes = ["cpVect", "cpTransform", "cpBB"]

# Helper functions
def snake_case(name):
    s1 = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1_\2', s1).lower()

def parse_param(s):
    s = s.strip()
    if s == "void": return None
    return tuple([x.strip() for x in s.split()])

def validate_type(t):
    return t in datatypes or t in resourcetypes

def parse_function(sig):
    # clean-up the string
    sig = sig.replace("*", "")
    sig = sig.replace(";", "")
    sig = sig.replace(")", "")
    sig = sig.replace("const ", "")
    sig = sig.strip()

    returnType, _, sig = sig.partition(" ")
    originalName, _, sig = sig.partition("(")
    params = sig.split(",")

    # change naming style and remove suffix
    funcName = snake_case(originalName)[3:]

    # discard some known functions
    if any(p.search(funcName) for p in ignoredPatterns):
        return None

    # found a good candidate
    #print funcName
    
    # parse parameters
    params = filter(None, map(parse_param, params))
    
    # validate them
    for param in params:
        # check type
        if not validate_type(param[0]):
            print "Unknown param type: ", param[0]
            print "> In function: ", funcName
            return None
    
    # validate return type
    if returnType != "void" and not validate_type(returnType):
        print "Unknown return type: ", returnType
        print "> In function: ", funcName
        return None

    return returnType, funcName, params, originalName

def convert_type(t):
    if t == "void":
        return t
    if t in resourcetypes:
        return "RID"
    return datatypes[t]

def gen_func_signature(func, with_class = False):
    returnType, name, params, _ = func
    sig = convert_type(returnType) + " "
    if with_class: sig += "ChipmunkServer::"
    sig += name + "("
    params = [convert_type(t) + " p_" + n for t, n in params]
    sig += ",".join(params).replace(",", ", ") + ")"
    return sig

def gen_func_definition(func):
    returnType, name, params, originalName = func
    sig = gen_func_signature(func, True)
    body = "\n{\n"
    if returnType in resourcetypes:
        body += "\t// TODO: return a RID\n"
    for param in params:
        if param[0] in resourcetypes:
            res = param[0][2:].lower()
            body += "\tauto *{1} = {0}_owner.get(p_{1});\n".format(res, param[1])
    args = []
    for param in params:
        if param[0] in resourcetypes:
            args.append(param[1])
        elif param[0] in mathTypes:
            args.append("CP(p_" + param[1] + ")")
        else:
            args.append("p_" + param[1])
    args = ",".join(args).replace(",", ", ")
    if returnType == "void":
        body += "\t{0}({1});\n".format(originalName, args)
    elif returnType in mathTypes:
        body += "\treturn GD({0}({1}));\n".format(originalName, args)
    else:
        body += "\treturn {0}({1});\n".format(originalName, args)
    return sig + body + "}"

def gen_func_binding(func):
    returnType, name, params, _ = func
    bind = "ObjectTypeDB::bind_method(_MD("
    bind += "\"{0}\"".format(name)
    for param in params:
        bind += ", \"{0}\"".format(param[1])
    bind += "), &ChipmunkServer::{0});".format(name)
    return bind

# read file
fname = sys.argv[1]
print "- Analysis -\n"

with open(fname) as f:
    lines = f.readlines()

methods = []
failed = []

for line in lines:
    # look for function signatures
    if line.strip().startswith("CP_EXPORT"):
        func = parse_function(line[9:])

        if func is not None:
            methods.append(func)
        else:
            failed.append(re.search(r"(\w+)\s*\(", line).group(1))

# output rejected functions
print "\n- Not Parsed -\n"
for method in failed:
    print method

# output declarations
print "\n/** Declarations */"
for method in methods:
    print gen_func_signature(method) + ";"

# output bindings
print "\n/** Bindings */"
for method in methods:
    print gen_func_binding(method)

# output definitions
print "\n/** Definitions */"
for method in methods:
    print "\n" + gen_func_definition(method)
