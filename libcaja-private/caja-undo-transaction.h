/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*- */

/* CajaUndoTransaction - An object for an undoable transaction.
 *                           Used internally by undo machinery.
 *                           Not public.
 *
 * Copyright (C) 2000 Eazel, Inc.
 *
 * Author: Gene Z. Ragan <gzr@eazel.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef CAJA_UNDO_TRANSACTION_H
#define CAJA_UNDO_TRANSACTION_H

#include <libcaja-private/caja-undo.h>

#define CAJA_TYPE_UNDO_TRANSACTION caja_undo_transaction_get_type()
#define CAJA_UNDO_TRANSACTION(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), CAJA_TYPE_UNDO_TRANSACTION, CajaUndoTransaction))
#define CAJA_UNDO_TRANSACTION_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), CAJA_TYPE_UNDO_TRANSACTION, CajaUndoTransactionClass))
#define CAJA_IS_UNDO_TRANSACTION(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CAJA_TYPE_UNDO_TRANSACTION))
#define CAJA_IS_UNDO_TRANSACTION_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), CAJA_TYPE_UNDO_TRANSACTION))
#define CAJA_UNDO_TRANSACTION_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), CAJA_TYPE_UNDO_TRANSACTION, CajaUndoTransactionClass))

/* The typedef for CajaUndoTransaction is in caja-undo.h
   to avoid circular deps */
typedef struct _CajaUndoTransactionClass CajaUndoTransactionClass;

struct _CajaUndoTransaction
{
    GObject parent_slot;

    char *operation_name;
    char *undo_menu_item_label;
    char *undo_menu_item_hint;
    char *redo_menu_item_label;
    char *redo_menu_item_hint;
    GList *atom_list;

    CajaUndoManager *owner;
};

struct _CajaUndoTransactionClass
{
    GObjectClass parent_slot;
};

GType                    caja_undo_transaction_get_type            (void);
CajaUndoTransaction *caja_undo_transaction_new                 (const char              *operation_name,
        const char              *undo_menu_item_label,
        const char              *undo_menu_item_hint,
        const char              *redo_menu_item_label,
        const char              *redo_menu_item_hint);
void                     caja_undo_transaction_add_atom            (CajaUndoTransaction *transaction,
        const CajaUndoAtom  *atom);
void                     caja_undo_transaction_add_to_undo_manager (CajaUndoTransaction *transaction,
        CajaUndoManager     *manager);
void                     caja_undo_transaction_unregister_object   (GObject                 *atom_target);
void                     caja_undo_transaction_undo                (CajaUndoTransaction *transaction);

#endif /* CAJA_UNDO_TRANSACTION_H */
