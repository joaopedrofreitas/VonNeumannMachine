.data

value:	 10
Z:	 0
vetor: 0,1,2,3

.text 		

main:
	li $t0, 25		# Load immediate value (25) 
	print $t0
	li $t5, 50		# Load immediate value (10) 
	print $t5
	li $t6, 5		# Load immediate value (5)
	print $t6
	li $t7, 12		# Load immediate value (12) 
	print $t7
	lw $t1, value		# Load the word stored in value (see bottom)
	print $t1
	add $t3, $t1, $t0	# Add
	print $t3
	sub $t4, $t0, $t1	# Subtract
	print $t4
	div $t8, $t5, $t6	# division
	print $t8
	sw $t4, Z		# Store the answer in Z (declared at the bottom)  
	print Z

	la $t0, vetor
	li $t2, 0 # Contador
	li $t3, 3 # Tamanho do vetor
	j print_vec
print_vec:
	print $t0
	li $t1, 1
	add $t0, $t1, $t0 # Aumenta o ponteiro do vetor
	add $t2, $t1 $t2 # Aumenta contador
	blti $t2 $t3 print_vec

comparacao:
	li $t1 10
	li $t2 5
	#beq $t1 $t1 igual
	#bne $t1 $t2 diferente
	#bgt $t1 $t2 maior
	#blt $t2 $t1 menor