r63028 | dinoex | 2002-07-15 15:08:01 -0500 (Mon, 15 Jul 2002) | 6 lines

- Fix Problem with HAVE_HOST_IN_UTMP
- update monitor.c

PR:             40576
Submitted by:   lxv@a-send-pr.sink.omut.org

r99768 | des | 2002-07-11 05:36:10 -0500 (Thu, 11 Jul 2002) | 6 lines

Use realhostname_sa(3) so the IP address will be used instead of the
hostname if the latter is too long for utmp.

Submitted by:   ru


--- loginrec.c.orig	2010-04-09 02:13:27.000000000 -0600
+++ loginrec.c	2010-09-14 16:14:12.000000000 -0600
@@ -179,6 +179,9 @@
 #ifdef HAVE_UTIL_H
 # include <util.h>
 #endif
+#ifdef __FreeBSD__
+#include <osreldate.h>
+#endif
 
 #ifdef HAVE_LIBUTIL_H
 # include <libutil.h>
@@ -693,8 +696,13 @@
 	strncpy(ut->ut_name, li->username,
 	    MIN_SIZEOF(ut->ut_name, li->username));
 # ifdef HAVE_HOST_IN_UTMP
+# if defined(__FreeBSD__) && __FreeBSD_version < 400000
 	strncpy(ut->ut_host, li->hostname,
 	    MIN_SIZEOF(ut->ut_host, li->hostname));
+# else
+	realhostname_sa(ut->ut_host, sizeof ut->ut_host,
+	    &li->hostaddr.sa, li->hostaddr.sa.sa_len);
+# endif
 # endif
 # ifdef HAVE_ADDR_IN_UTMP
 	/* this is just a 32-bit IP address */
