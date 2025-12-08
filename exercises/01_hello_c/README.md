# Exercise 01: Hello C in WebAssembly

## 🎯 Goal
Compile your first C program to WebAssembly and run it in the browser.

## 📝 Assignment
1. Create a simple C program (`hello.c`) that prints "Hello from WebAssembly!" to the console
2. Compile it to WebAssembly using Emscripten
3. Run it in the browser and verify the output in the console

## 🔨 Steps

### Step 1: Write the C code
Create `hello.c`:
```c
#include <stdio.h>

int main() {
    printf("Hello from WebAssembly!\n");
    return 0;
}
```

### Step 2: Compile to WebAssembly
```bash
emcc hello.c -o hello.html
```

This generates:
- `hello.html` - HTML page to run your code
- `hello.js` - JavaScript glue code
- `hello.wasm` - The WebAssembly binary

### Step 3: Run the application
```bash
npm run serve:hello
```

Or use:
```bash
npx http-server . -p 8081
```

### Step 4: Test
Open your browser to `http://localhost:8081/hello.html` and check the console (F12) for the message.

## ✅ Success criteria
- You see "Hello from WebAssembly!" in the browser console
- All three files (`.html`, `.js`, `.wasm`) are generated
- You understand the basic compilation flow

## 💡 Bonus challenges
- Add more `printf` statements
- Try compiling with optimization: `emcc hello.c -O3 -o hello.html`
- Compare file sizes with and without optimization
