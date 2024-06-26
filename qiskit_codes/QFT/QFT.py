import numpy as np
from qiskit import QuantumCircuit, transpile, ClassicalRegister, QuantumRegister
from qiskit.providers.aer import QasmSimulator
from qiskit.circuit.library import QFT

pi = np.pi

simulator = QasmSimulator()

q = QuantumRegister(5,'q')
c = ClassicalRegister(5,'c')

qc = QuantumCircuit(q, c)

qc.x(q[4])
qc.x(q[2])
qc.x(q[0])

qc += QFT(num_qubits=5, approximation_degree=0, do_swaps=True, inverse=False, insert_barriers=True, name='qft')

qc.measure(q,c)

compiled_circuit = transpile(qc, simulator)
job = simulator.run(compiled_circuit, shots=1024)
result = job.result()
counts = result.get_counts(compiled_circuit)

print(qc.draw(output='text', cregbundle=False, fold=1000))
print(counts)

q = QuantumRegister(5,'q')
c = ClassicalRegister(5,'c')

qc = QuantumCircuit(q,c)

qc.x(q[4])
qc.x(q[2])
qc.x(q[0])
qc+= QFT(num_qubits=5, approximation_degree=0, do_swaps=True, inverse=False, insert_barriers=True, name='qft')
qc+= QFT(num_qubits=5, approximation_degree=0, do_swaps=True, inverse=True, insert_barriers=True, name='qft')
qc.measure(q,c)

compiled_circuit = transpile(qc, simulator)
job = simulator.run(compiled_circuit, shots=1024)
result = job.result()
counts = result.get_counts(compiled_circuit)

print("\n QFT with inverse QFT Output")
print("------------------------------")
print(qc.draw(output='text', cregbundle=False, fold=1000))
print(counts)
