/*
 * Copyright (c) 2015 The Linux Foundation. All rights reserved.
 *
 * Previously licensed under the ISC license by Qualcomm Atheros, Inc.
 *
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * This file was originally distributed by Qualcomm Atheros, Inc.
 * under proprietary terms before Copyright ownership was assigned
 * to the Linux Foundation.
 */

/**
 * DOC : wlan_hdd_memdump.c
 *
 * WLAN Host Device Driver file for dumping firmware memory
 *
 */

#include <sme_Api.h>
#include <wlan_hdd_includes.h>
#include "wlan_hdd_memdump.h"
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/proc_fs.h> /* Necessary because we use the proc fs */
#include <linux/uaccess.h> /* for copy_to_user */

/** memdump_get_file_data() - get data available in proc file
 *
 * @file - handle for the proc file.
 *
 * This function is used to retrieve the data passed while
 * creating proc file entry.
 *
 * Return: void pointer to hdd_context
 */
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 0)) || defined(WITH_BACKPORTS)
static void *memdump_get_file_data(struct file *file)
{
	void *hdd_ctx;

	hdd_ctx = PDE_DATA(file_inode(file));
	return hdd_ctx;
}
#else
static void *memdump_get_file_data(struct file *file)
{
	void *hdd_ctx;

	hdd_ctx = PDE(file->f_path.dentry->d_inode)->data;
	return hdd_ctx;
}
#endif

