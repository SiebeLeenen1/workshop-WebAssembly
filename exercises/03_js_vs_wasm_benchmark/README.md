# Exercise 03: JavaScript vs WebAssembly Performance Benchmark

## 🎯 Goal
Compare the execution speed of JavaScript vs WebAssembly for computationally intensive tasks.

## 📝 Assignment
1. Write a heavy computation function in both JavaScript and C
2. Benchmark both implementations
3. Compare the results and understand the performance differences

## 🔨 Steps

### Step 1: Write the C computation
Create `loop.c`:
```c
#include <emscripten/emscripten.h>

EMSCRIPTEN_KEEPALIVE
long heavy_sum(int limit) {
    long sum = 0;
    for (int i = 0; i < limit; i++) {
        sum += i * i;
    }
    return sum;
}
```

### Step 2: Compile to WebAssembly
```bash
emcc loop.c -O3 -s EXPORTED_FUNCTIONS='["_heavy_sum"]' -o loop.js
```

### Step 3: Create the benchmark HTML
Create `index.html`:
```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>JS vs Wasm Performance Test</title>
  </head>
  <body>
    <h1>JS vs Wasm Performance Test</h1>
    <button id="run">Run Benchmark</button>
    <pre id="output"></pre>
    <script src="loop.js"></script>
    <script src="script.js"></script>
  </body>
</html>
```

### Step 4: Write the benchmark script
Create `script.js`:
```javascript
// JavaScript implementation
function heavySumJS(limit) {
  let sum = 0;
  for (let i = 0; i < limit; i++) {
    sum += i * i;
  }
  return sum;
}

var Module = {
  onRuntimeInitialized: function() {
    document.getElementById("run").onclick = () => {
      const iterations = 10000000; // 10 million
      const output = document.getElementById("output");
      output.textContent = "Running benchmark...\n";
      
      // Benchmark JavaScript
      const jsStart = performance.now();
      const jsResult = heavySumJS(iterations);
      const jsEnd = performance.now();
      const jsTime = jsEnd - jsStart;
      
      // Benchmark WebAssembly
      const wasmStart = performance.now();
      const wasmResult = Module._heavy_sum(iterations);
      const wasmEnd = performance.now();
      const wasmTime = wasmEnd - wasmStart;
      
      // Display results
      output.textContent = `
Results (${iterations.toLocaleString()} iterations):
===========================================

JavaScript:
  Time: ${jsTime.toFixed(2)} ms
  Result: ${jsResult}

WebAssembly:
  Time: ${wasmTime.toFixed(2)} ms
  Result: ${wasmResult}

Performance:
  Speedup: ${(jsTime / wasmTime).toFixed(2)}x faster
  Difference: ${(jsTime - wasmTime).toFixed(2)} ms
      `;
    };
  }
};
```

### Step 5: Run the benchmark
```bash
npm run build:benchmark
npm run serve:benchmark
```

Open `http://localhost:8081/index.html` and click "Run Benchmark"

## ✅ Success criteria
- Both JavaScript and WebAssembly produce the same result
- You can see the execution time difference
- WebAssembly is typically 2-10x faster (depends on browser and CPU)
- You understand when WebAssembly provides performance benefits

## 💡 Bonus challenges
- Try different iteration counts (1M, 50M, 100M)
- Implement other algorithms (Fibonacci, prime numbers, matrix operations)
- Add a chart to visualize the performance difference
- Test with different optimization levels: `-O0`, `-O1`, `-O2`, `-O3`, `-Oz`
- Run the benchmark multiple times and calculate average

## 📊 Expected results
WebAssembly typically excels at:
- Heavy numerical computations
- Loops with many iterations
- Integer arithmetic
- No DOM manipulation

JavaScript may be faster for:
- Small computations (overhead)
- Frequent DOM access
- String manipulation
- Object-oriented code
