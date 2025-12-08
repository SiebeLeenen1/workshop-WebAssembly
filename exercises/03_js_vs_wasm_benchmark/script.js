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
