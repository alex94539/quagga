#include <zebra.h>

#include "zebra/rib.h"
#include "zebra/rt.h"
#include "zebra/ioctl.h"

void ifreq_set_name (struct ifreq *a, struct interface *b) { return; }
int if_set_mtu (struct interface *ifp, int mtu) { return 0; }

int if_set_prefix (struct interface *a, struct connected *b)
{ 
  kernel_address_add_ipv4 (a, b);
  return 0;
}

int if_unset_prefix (struct interface *a, struct connected *b)
{ 
  kernel_address_delete_ipv4 (a, b);
  return 0;
}

int if_prefix_add_ipv6 (struct interface *a, struct connected *b) { return 0; }
#ifdef HAVE_SYS_WEAK_ALIAS_PRAGMA
#pragma weak if_prefix_delete_ipv6 = if_prefix_add_ipv6
#else
int if_prefix_delete_ipv6 (struct interface *a, struct connected *b) { return 0; }
#endif

int if_ioctl (u_long a, caddr_t b) { return 0; }

int if_set_flags (struct interface *a, uint64_t b) { return 0; }
#ifdef HAVE_SYS_WEAK_ALIAS_PRAGMA
#pragma weak if_unset_flags = if_set_flags
#else
int if_unset_flags (struct interface *a, uint64_t b) { return 0; }
#endif

void if_get_flags (struct interface *a) { return; }
#ifdef HAVE_SYS_WEAK_ALIAS_PRAGMA
#pragma weak if_get_metric = if_get_flags
#pragma weak if_get_mtu = if_get_flags
#else
/* void if_get_metric (struct interface *a) { return; } */
/* void if_get_mtu (struct interface *a) { return; } */
#endif

#ifdef SOLARIS_IPV6
#pragma weak if_ioctl_ipv6 = if_ioctl
struct connected *if_lookup_linklocal(struct interface *a) { return 0; }

#define AF_IOCTL(af, request, buffer) \
        ((af) == AF_INET? if_ioctl(request, buffer) : \
                          if_ioctl_ipv6(request, buffer))
#else /* SOLARIS_IPV6 */

#define AF_IOCTL(af, request, buffer)  if_ioctl(request, buffer)

#endif /* SOLARIS_IPV6 */
