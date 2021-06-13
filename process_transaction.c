#include "danni_i_funcii.h"
#include <stdio.h>
#include <string.h>

struct smetka *find_smetka(struct smetka_t *smetki, char *spec)
{
    for (struct smetka *current = smetki->head; current != NULL; current = current->next)
    {
        if (strcmp(spec, current->spec) == 0)
            return current;
    }
    return NULL;
}

void process_transaction(struct transaction *txn, struct smetka_t *smetki)
{
    struct smetka *from = find_smetka(smetki, txn->spec1);
    struct smetka *to = find_smetka(smetki, txn->spec2);

    if (from == NULL)
    {
        printf("Error! Invalid account: %s\n", txn->spec1);
        return;
    }

    if (to == NULL)
    {
        printf("Error! Invalid account: %s\n", txn->spec2);
        return;
    }

    if (from->balans < txn->transaction)
    {
        printf("Error! Insufficient funds in account %s\n", txn->spec1);
        return;
    }

    from->balans -= txn->transaction;
    to->balans += txn->transaction;
    save_smetki(smetki);
}

void process_transactions(struct transaction_t *txn_list, struct smetka_t *smetki)
{
    struct transaction *txn = txn_list->head;

    while (txn != NULL)
    {
        process_transaction(txn, smetki);
        txn_list->head = txn->next;
        free(txn);
        save_transactions(txn_list);
    }
}