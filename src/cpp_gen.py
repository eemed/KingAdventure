#!/usr/bin/env python3
def generate_header(filename, namespaces, indent):
    with open(filename + '.h', "w") as fout:
        indentation = indent * ' '
        indent_level = 0;
        fout.write('#ifndef _' + filename.upper() + '_\n' )
        fout.write('#define _' + filename.upper() + '_\n' )
        for name in namespaces:
            fout.write(indent_level * indentation + 'namespace ' + name + '\n' + indent_level * indentation + '{\n' )
            indent_level += 1
        fout.write(indent_level * indentation + 'class ' + filename[0].upper() + filename[1:] + '\n' )
        fout.write(indent_level * indentation + '{' + '\n' )
        indent_level += 1
        fout.write(indent_level * indentation + 'private:' + '\n\n' )
        fout.write(indent_level * indentation + 'public:' + '\n' )
        indent_level += 1
        fout.write(indent_level * indentation + filename[0].upper() + filename[1:] + '();\n\n' )
        indent_level -= 2
        fout.write(indent_level * indentation + '};' + '\n' )
        indent_level -= 1
        namespaces.reverse()
        for name in namespaces:
            fout.write(indent_level * indentation + '} // ' + name + '\n' )
            indent_level -= 1
        fout.write('#endif // _' + filename.upper() + '_' )

def generate_body(filename, namespaces, indent):
    with open(filename + '.cpp', "w") as fout:
        indentation = indent * ' '
        indent_level = 0;
        fout.write('#include "' + filename + '.h"\n' )
        for name in namespaces:
            fout.write(indent_level * indentation + 'namespace ' + name + '\n' + indent_level * indentation + '{\n' )
            indent_level += 1
        fout.write('\n\n' )
        indent_level -= 1
        namespaces.reverse()
        for name in namespaces:
            fout.write(indent_level * indentation + '} // ' + name + '\n' )
            indent_level -= 1

if __name__ == '__main__':
    filename = input("Filename: ")
    namespace = input("Namespaces: ")
    indent = int(input("indentation: "))
    generate_header(filename, namespace.split(), indent)
    generate_body(filename, namespace.split(), indent)
