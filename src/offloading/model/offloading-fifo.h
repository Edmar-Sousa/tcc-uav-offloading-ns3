#ifndef __OFFLOADING_FIFO_H__
#define __OFFLOADING_FIFO_H__

#include "offloading-decision.h"

namespace Offloading 
{

namespace Algorithm 
{

class FIFOAlgorithm: public IOffloadingDecision
{
public:
    FIFOAlgorithm();
    ~FIFOAlgorithm();

    ns3::Ipv4Address offloadingDecision() override;
};

/**
 *    O servidor deve receber um pacote do cliente. Esse pacote
 *    deve ser "processado" e então enviar uma resposta. Contudo,
 *    os seguintes pontos devem ser considerados:
 *
 *    1 - Como determinar o tempo que o processamento ira durar? (Delay
 *        para responder, simulando o processamento).
 *
 *    2 - Com base na potência da CPU como extimar o uso energético?
 *
 *    3 - Como produzir o gráfico contendo o consumo energético do servidor
 *        durante a simulação?
 *
 *    4 - O servidor deve armazenar as tarefas em uma fila?
 *
 */




 /**
 *    O cliente deve executar o algortimo de decisão de
 *    offloading, em seguida enviar o pacote para o servidor e
 *    esperar uma resposta.
 *
 *    Inicialmente será implementado o FIFO, algoritmo que envia
 *    a tarefa para todos os servidores e espera o primeiro a
 *    responder.
 *
 *    Contudo, isso levanta alguns ponto a serem considerados:
 *
 *    1 - Como descobrir os servidores de computação que estão proximos?
 *
 *    2 - Como medir os parâmetros: número de falhas e consumo energético?
 *
 *
 *    TODO: Lista de tarrefas para conseguir os objetivos acima.
 *
 *    1 - Implementar a simulação com hosts estaticos.
 *
 *    2 - Adicionar um conjunto de logs para debugar o funcionamento do
 *        Algoritmo.
 *
 *    3 - Abstrair a classe para ser facilitar a implementação dos próximos
 *        Algoritmos.
 *
 *    4 - Adicionar um movimento básico no host cliente para validar a simulação.
 */
};

};


#endif