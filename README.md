Tarefa: Controle de Servomotor por PWM com Raspberry Pi Pico W

Este projeto foi desenvolvido individualmente como parte de uma tarefa.

Link do vídeo: https://www.youtube.com/watch?v=zc0r_OaaLMg

Este repositório contém a implementação de um sistema de controle de servomotor utilizando o módulo PWM do microcontrolador Raspberry Pi Pico W. O projeto foi desenvolvido como parte da atividade proposta na unidade 4, capítulo 7, da disciplina ministrada pelo Prof. Dr. Ricardo Menezes Prates.

Descrição do Projeto

O objetivo desta tarefa é simular o controle de um servomotor utilizando o módulo PWM do RP2040. O sistema foi implementado no simulador Wokwi, e o código foi desenvolvido em C utilizando o Pico SDK. Além disso, foi realizado um experimento com o LED RGB (GPIO 12) utilizando a ferramenta BitDogLab.

Componentes Utilizados

    Microcontrolador Raspberry Pi Pico W.

    Servomotor – motor micro servo padrão (simulado no Wokwi integrado).

    LED RGB (GPIO 12) para experimento com BitDogLab.

Requisitos da Tarefa

    Configurar a frequência de PWM para 50Hz na GPIO 22.

    Definir o ciclo ativo do PWM para:

        2.400µs (180 graus) e aguardar 5 segundos.

        1.470µs (90 graus) e aguardar 5 segundos.

        500µs (0 graus) e aguardar 5 segundos.

    Implementar uma rotina para movimentação suave do servomotor entre 0 e 180 graus.

    Realizar um experimento com o LED RGB (GPIO 12) utilizando a ferramenta BitDogLab.

Passos para Execução

    Para executar, clone o repositório, compile e grave para execultar os testes na placa BitDogLab

    git clone https://github.com/RamonPetitinga/tarefa_U4C6012T.git

    Abra o projeto no VS Code.

    Execute a simulação no Wokwi.

    Para o experimento com o LED RGB, utilize a ferramenta BitDogLab conforme descrito no código.

Experimentos e Resultados

Controle do Servomotor

    O servomotor é controlado com movimentos suaves entre 0 e 180 graus, utilizando incrementos de 5µs no ciclo ativo do PWM.

    O comportamento do servomotor foi validado no simulador Wokwi.

Experimento com LED RGB

    O LED RGB (GPIO 12) foi controlado proporcionalmente ao ciclo ativo do PWM.

    Efetuando a alteração da porta GPIO de 22 para 12 conseguimos realizar o teste do LED na BitDogLab, foi possível observar a variação de brilho do LED em sincronia com o movimento do servomotor.
