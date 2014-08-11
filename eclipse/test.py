import argparse
import os
import subprocess

def parseArgs():
    parser = argparse.ArgumentParser()
    parser.add_argument('base_path',
                        help='Path to algorithmic code')
    parser.add_argument('-d', '--debug',
                        help='Run in debugger mode',
                        action='store_true')
    parser.add_argument('-i', '--input',
                        help='Input file',
                        default='in/in')
    parser.add_argument('-o', '--output',
                        help='Output file',
                        default='out/out')
    parser.add_argument('-e', '--expected_output',
                        help='Expected output')
    parser.add_argument('-v', '--verbose',
                        help='Verbose printing.',
                        action='store_true')
    parser.add_argument('-c', '--compare',
                        help='compare output with output of this program.')
    parser.add_argument('-g', '--generator',
                        help='input generator.')
    return parser.parse_args()


def main():
    args = parseArgs()
    # Fail if base path does not exists!
    if not os.path.exists(args.base_path):
        print 'Arena: ', args.base_path, 'does not exist!'
        return 1
    # Create bin folder if it does not exist.
    subprocess.call(['mkdir', '-p', os.path.join(args.base_path, 'bin')])
    main_file = os.path.join(args.base_path, 'main.cpp')
    exec_file = os.path.join(args.base_path, 'bin/main')
    compile_file = os.path.join(args.base_path, 'bin/compile_output')
    input_file = os.path.join(args.base_path, args.input)
    output_file = os.path.join(args.base_path, args.output)
    if args.generator:
        gen_cpp = os.path.join(args.base_path, args.generator)
        gen_out = os.path.join(args.base_path, 'bin/input_generator')
        compile_command = ['g++', gen_cpp, '-o', gen_out]
        print 'Compiling: ', ' '.join(compile_command)
        f_compile_output = open(compile_file, 'w')
        subprocess.call(compile_command, stdout = f_compile_output, stderr=f_compile_output)
        f_compile_output.close()
        
        # Check for compile errrors
        f_compile_output = open(compile_file)
        compile_output = f_compile_output.read()
        if len(compile_output) > 0:
            print compile_output
            return 1
        print 'Generating input...'
        f_input = open(input_file, 'w')
        subprocess.call(gen_out, stdout=f_input)
    if args.compare:
        compare_cpp = os.path.join(args.base_path, args.compare)
        compare_exec = os.path.join(args.base_path, 'bin/compare')
        args.expected_output = 'bin/output_comp'
        comp_output_file = os.path.join(args.base_path, args.expected_output)
        compile_command = ['g++', compare_cpp, '-o', compare_exec]
        print 'Compiling: ', ' '.join(compile_command)
        f_compile_output = open(compile_file, 'w')
        subprocess.call(compile_command, stdout = f_compile_output, stderr=f_compile_output)
        f_compile_output.close()
        
        # Check for compile errrors
        f_compile_output = open(compile_file)
        compile_output = f_compile_output.read()
        if len(compile_output) > 0:
            print compile_output
            return 1
        print 'Generating output...'
        f_input = open(input_file)
        f_output = open(comp_output_file, 'w')
        subprocess.call(compare_exec, stdin=f_input, stdout=f_output)

    if args.verbose:
        print 'Main File:', main_file
        print 'Exec File:', exec_file
        print 'Input File:', input_file
        print 'Output File:', output_file
    if args.debug:
        compile_command = ['g++',
                           '-DJAI_ARENA',
                           main_file,
                           '-o',
                           exec_file]
    else:
        compile_command = ['g++',
                           main_file,
                           '-o',
                           exec_file]

    print 'Compiling: ', ' '.join(compile_command)
    f_compile_output = open(compile_file, 'w')
    subprocess.call(compile_command, stdout = f_compile_output, stderr=f_compile_output)
    f_compile_output.close()
    
    # Check for compile errrors
    f_compile_output = open(compile_file)
    compile_output = f_compile_output.read()
    if len(compile_output) > 0:
        print compile_output
        return 1

    # Generate output from input file
    print 'Running...'
    f_input = open(input_file)
    f_output = open(output_file, 'w')
    subprocess.call(exec_file, stdin=f_input, stdout=f_output)
    f_output.close()

    # Generate output diff
    if args.expected_output:
        diff_file = os.path.join(args.base_path, 'bin/diff_output')
        f_diff = open(diff_file, 'w')
        exoutput_file = os.path.join(args.base_path, args.expected_output)
        subprocess.call(['diff', output_file, exoutput_file], stdout=f_diff)
        f_diff = open(diff_file, 'r')
        diff_error = f_diff.read()
        if len(diff_error) > 0:
            print '==== DIFF FAILED ===='
            print diff_error
        else:
            print '==== SUCCESS ====='


if __name__ == '__main__':
    main()
