# Comunicar dois processos através de Fila (Troca de Mensagens)

## Enunciado

Utilizando troca de mensagens, suponha 2 processos P1 e P2:

* P1 gera um vetor de caracteres V
* P1 envia V para P2 por mensagem
* P2 conta o número de ocorrências de um determinado caracter em V
* P2 envia para P1, por mensagem, a número de ocorrências do caracter
* P1 exibe o número de ocorrências

*Observe que não existe a relação pai-filho entre os processos P1 e P2.*

## Lógica adotada

Foram feitos dois códigos, um chamado *consumer*, correspondente ao *P2* do enunciado, e outro chamado *producer*, correspondente ao *P1* do enunciado. O *producer* é o responsável por gerar o vetor e passar as informações para a fila, enquanto o *consumer* é o responsável por acessar a fila, e fazer a devida contagem dos caracteres e retornar o resultado da contagem para a fila, para que o *producer* tenha acesso.

## Execução

Compile e execute o *consumer*. Após isso, teremos a seguinte mensagem impressa na tela: "1 - Esperando dados de entrada...", conforme imagem abaixo. Nesse ponto, a fila já foi criada e o *consumer* está esperando que algum dado chegue na fila.

![Primeiro passo Consumer](./imagens/passo1_consumer.png)

Agora, precisamos rodar o *producer*, para ele gerar o vetor e inserí-lo na fila. Para isso, basta compilar e executar, conforme imagem abaixo. Será impresso na tela o vetor que foi gerado, e uma mensagem de espera do resultado.

![Segundo Passo Producer](./imagens/passo1_producer.png)

Após isso, o *consumer* irá perceber que foi inserido um novo item na fila, e irá ler e fazer a devida contagem, conforme imagem:

![Segundo passo Consumer](./imagens/passo2_consumer.png)

Após a contagem, o *consumer* irá enviar o resusltado através da fila e já estará pronto para receber um novo dado.

![Terceiro passo Consumer](./imagens/passo4_consumer.png)

O *producer*, após pegar o resultado postado na fila, imprime o valor na tela.

![Segundo passo producer](./imagens/passo2_producer.png)

Com isso, temos o término da execução do nosso codigo.

## Validação

Para validar a contagem, colou-se o vetor gerado em um arquivo de texto, e utilizou-se a função de busca, conforme pode ser visto na imagem abaixo, confirmando a contagem de 21 caracteres 'I'.

![Validação](./imagens/validacao.png)




