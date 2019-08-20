#ifndef __FUNC_LIB

#define __FUNC_LIB

/**
 * Imprime os datos das usuarios contidos no árbol,
 * o seu nome e as transferencias emitidas
 * @param aTransferencias Debe estar correctamente inicializado
 */
void imprimirUsuarios(abb* aTransferencias);

/**
 * Mostra o grafo global de transferencias
 * @param gTransferencias Debe estar correctamente inicializado
 */
void imprimirGrafoGlobal(grafo gTransferencias);

/**
 * Mostra por pantalla o número de usuarios rexistrados, o número medio
 * de amigos por usuario, o usuario que emite transferencias a un
 * maior número de usuarios e o que recibe máis transferencias de máis
 * usuarios
 * @param gTransferencias Debe estar correctamente inicializado
 */
void obterEstatisticasGlobais(grafo gTransferencias);

/**
 * Mostrarase o nome, grado de entrada e grado de saída dos usuarios
 * máis activos
 * @param gTransferencias Debe estar correctamente inicializado
 */
void usuariosMaisActivos(grafo gTransferencias);

/**
 * Busca os datos dun usuario no arbol binario de busqueda
 * e eliminaos, xunto coa información das transferencias
 * que recibiu.
 * @param aTransferencias Debe estar correctamente inicializado
 */
void eliminarUsuario(abb* aTransferencias, grafo* gTransferencias, tipoclave usuario);

/**
 * Permite introducir os datos dunha transferencia
 * e os datos correspondentes ao emisor e receptor
 * da mesma no arbol binario de búsqueda <aTransferencias>.
 * @param aTransferencias Debe estar correctamente inicializado
 * @param emisor Nome do emisor da transferencia
 */
void introducirTransferencia(abb* aTransferencias, grafo* gTransferencias, tipoelem informacionEmisor);

/**
 * Busca os datos dun usuario no arbol binario de busqueda
 * e mostraos, xunto ca súa última transferencia que
 * realizou.
 * @param aTransferencias Debe estar correctamente inicializado
 * @param gTransferencias Debe estar correctamente inicializado
 * @param informacionEmisor Debe ter o campo nomeUsuario correctamente inicializado
 */
void consultaPorUsuario(abb* aTransferencias, tipoelem informacion);

/**
 * Busca os datos dun usuario no arbol binario de busqueda
 * e mostra as transferencias que recibiu, xunto cos datos
 * das mesmas.
 * @param aTransferencias Debe estar correctamente inicializado
 * @param informacion Debe ter o campo nomeUsuario correctamente inicializado
 */
void consultaPorReceptor(abb* aTransferencias, tipoelem informacion);

/**
 * Busca os datos dun usuario no arbol binario de busqueda
 * e mostra as estatisticas das transferencias das que é
 * emisor, isto é, a cantidade total transferida e a
 * transferencia de maior importe.
 * @param aTransferencias Debe estar correctamente inicializado
 * @param informacion Debe ter o campo nomeUsuario correctamente inicializado
 */
void obterEstatisticasUsuario(abb* aTransferencias, tipoelem informacion);

/**
 * Eliminamos as relacións existentes entre o usuario dado e un que
 * que se pedirá ao mesmo co que debe ter unha relación de amistade
 * @param aTransferencias Debe estar correctamente inicializado
 * @param gTransferencias Debe estar correctamente inicializado
 * @param informacion Debe ter o campo nomeUsuario correctamente inicializado
 */
void borrarAmigo(abb* aTransferencias, grafo* gTransferencias, tipoelem informacion);

/**
 * Imprime todos os datos de transerencias contidos
 * no arbol binario de búsqueda e destrúeo,
 * liberando a memoria reservada para cada un dos seus nodos.
 * @param aTransferencias Debe estar correctamente inicializado
 */
void sairPrograma(abb* aTransferencias, grafo* gTransferencias);

/**
 * Lee un arquivo de datos, que conterá informacion sobre as transferencias
 * realizadas e garda esta inforacion no arbol de transferencias
 * @param aTransferencias Debe estar correctamente inicializado
 * @param ficheiro Nome do ficheiro donde leer os datos, debe ter o formato adecuado
 */
void lecturaDatos(abb* aTransferencias, grafo* gTransferencias, char* ficheiro);

/**
 * Garda a informacion das transferencias almacenadas no arbol de transferencias
 * nun arquivo, pasa
 * @param aTransferencias Debe estar correctamente inicializado
 * @param ficheiro Nome do ficheiro donde leer os datos, debe ter o formato adecuado
 */
void escrituraDatos(abb* aTransferencias, char* ficheiro);

/**
 * Abre o menú de usuario que permite ao mesmo realizar unha trasnferencia
 * consultar as súas transferencias emitidas e recibidas, mostrar as súas estatisticas,
 * darse de baixa na aplicación ou borrar un amigo
 * @param aTransferencias Debe estar correctamente inicializado
 * @param gTransferencias Debe estar correctamente inicializado
 */
void menuUsuario(abb* aTransferencias, grafo* gTransferencias, tipoelem informacion);

/**
 * Abre o menú de administrador que proporciona as funcionalidades de
 * imprimir usuarios, imprimir grafo global, mostrar as estatisticas
 * globais, os usuarios máis activos e permite dar de baixa a un
 * usuario
 * @param aTransferencias Debe estar correctamente inicializado
 * @param gTransferencias Debe estar correctamente inicializado
 */
void menuAdministrador(abb* aTransferencias, grafo* gTransferencias);

/**
 * Abre un menú que dá acceso aos dous menús que proporciona a
 * aplicación: usuario e administrador
 * @param aTransferencias Debe estar correctamente inicializado
 * @param gTransferencias Debe estar correctamente inicializado
 */
void login(abb* aTransferencias, grafo* gTransferencias);

#endif
