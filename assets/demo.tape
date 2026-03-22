# Output settings
Output demo.gif
Set FontSize 20
Set Width 1200
Set Height 800
Set Theme "Catppuccin Mocha"
Set Padding 40
Set TypingSpeed 60ms

# --- START THE SHOW ---
# show source code
Type "cat lang_examples/factorial.toy" Sleep 500ms Enter
Sleep 3s

# 2. Show the LLVM IR generation (-S flag)
Type "./build/compiler lang_examples/factorial.toy -S" Sleep 500ms Enter
Sleep 4s
Ctrl+L # Clear screen for next step

#Demonstrate JIT mode (-jit flag)
Type "./build/compiler lang_examples/factorial.toy -jit" Sleep 500ms Enter
Sleep 2s
Ctrl+L

#compile to a native binary
Type "./build/compiler lang_examples/factorial.toy -o factorial" Sleep 500ms Enter
Sleep 1s
Type "ls -l lang_examples/" Sleep 500ms Enter
Sleep 2s

# Run the final executable
Type "./a.out" Sleep 500ms Enter
Sleep 3s

# Exit gracefully
Type "echo 'Compilation Complete.'" Enter
Sleep 2s