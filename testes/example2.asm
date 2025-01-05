.data

# Declaração de variáveis
value:  20
Z:      0
vetor:  0, 1, 2, 3, 4, 5
result: 0

.text

# Função principal
main:
    li $t0, 40             # Carregar valor imediato (40) no registrador t0
    li $t1, 25             # Carregar valor imediato (25) no registrador t1
    print_val $t0          # Chama a função print_val para imprimir $t0
    print_val $t1          # Chama a função print_val para imprimir $t1

    lw $t2, value          # Carregar o valor armazenado em 'value' no registrador t2
    print_val $t2          # Chama a função print_val para imprimir o valor de $t2

    add $t3, $t2, $t0      # Soma os valores de $t2 e $t0 e armazena no registrador t3
    print_val $t3          # Chama a função print_val para imprimir o resultado da soma

    sub $t4, $t0, $t1      # Subtrai os valores de $t0 e $t1 e armazena no registrador t4
    print_val $t4          # Chama a função print_val para imprimir o resultado da subtração

    sw $t4, Z              # Armazena o resultado da subtração em 'Z'
    print_val Z            # Chama a função print_val para imprimir o valor de Z

    # Manipulação do vetor em múltiplos núcleos
    la $t5, vetor          # Carrega o endereço base do vetor
    li $t6, 0              # Inicializa o contador do vetor
    li $t7, 6              # Define o tamanho do vetor (6 elementos)

loop_vetor:
    # Processo de leitura e manipulação do vetor sem risco de deadlock
    lw $t8, 0($t5)         # Carrega o valor do vetor na posição corrente
    add $t9, $t8, $t0      # Soma o valor do vetor com $t0
    sw $t9, result         # Armazena o resultado na variável 'result'
    print_val result       # Chama a função print_val para imprimir o resultado
    
    # Atualiza ponteiro do vetor e contador
    addi $t5, $t5, 4       # Incrementa o ponteiro do vetor (4 bytes por elemento)
    addi $t6, $t6, 1       # Incrementa o contador

    blt $t6, $t7, loop_vetor # Se o contador for menor que o tamanho do vetor, repete

    # Comparações entre valores
comparacao:
    li $t1, 30             # Carrega valor imediato 30
    li $t2, 15             # Carrega valor imediato 15
    
    # Operações de comparação
    beq $t1, $t2, iguais   # Se $t1 igual a $t2, desvia para 'iguais'
    bne $t1, $t2, diferentes # Se $t1 diferente de $t2, desvia para 'diferentes'
    bgt $t1, $t2, maior    # Se $t1 maior que $t2, desvia para 'maior'
    blt $t1, $t2, menor    # Se $t1 menor que $t2, desvia para 'menor'

iguais:
    print_val "Valores Iguais"
    j comparacao_end

diferentes:
    print_val "Valores Diferentes"
    j comparacao_end

maior:
    print_val "Valor $t1 é maior"
    j comparacao_end

menor:
    print_val "Valor $t1 é menor"
    j comparacao_end

comparacao_end:

    end_program:
    # Finaliza a execução do programa
    print_val "Fim da Execução"
    end

# Função para imprimir valores
print_val:
    # Recebe um registrador e imprime o valor
    move $a0, $t0           # Move valor de $t0 para $a0 (usado para impressão)
    syscall                  # Chama a syscall de impressão
    jr $ra                   # Retorna da função

