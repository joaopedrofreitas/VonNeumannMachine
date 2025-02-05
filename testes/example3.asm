.data

value:	 10
Z:	 0

.text 		

main:
	li $t0, 25		# Load immediate value (25) 
	print $t0
	lw $t1, value		# Load the word stored in value (see bottom)
	print $t1
	sub $t4, $t0, $t1	# Subtract
	print $t4
	sw $t4, Z		# Store the answer in Z (declared at the bottom)  
	print Z

comparacao:
	li $t1 10
	li $t2 5
	#beq $t1 $t1 igual
	#bne $t1 $t2 diferente
	#bgt $t1 $t2 maior
	#blt $t2 $t1 menor
