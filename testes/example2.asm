.data

value:	 10
Z:	 0
vetor: 0,1,2,3

.text 		

main:
	li $t5, 25		# Load immediate value (25) 
	print $t5
	lw $t6, value		# Load the word stored in value (see bottom)
	print $t6
	add $t8, $t6, $t5	# Add
	print $t8
	sub $t9, $t5, $t6	# Subtract
	print $t9
	sw $t9, Z		# Store the answer in Z (declared at the bottom)  
	print Z

	la $t5, vetor
	li $t7, 0 # Contador
	li $t8, 3 # Tamanho do vetor
	j print_vec
print_vec:
	print $t5
	li $t6, 1
	add $t5, $t6, $t5 # Aumenta o ponteiro do vetor
	add $t7, $t6 $t7 # Aumenta contador
	blti $t7 $t8 print_vec

comparacao:
	li $t6 10
	li $t7 5
	#beq $t6 $t6 igual
	#bne $t6 $t7 diferente
	#bgt $t6 $t7 maior
	#blt $t7 $t6 menor
