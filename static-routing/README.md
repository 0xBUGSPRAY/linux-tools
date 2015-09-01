# Static Routing

Problem:

    * Two internet connections available through two NIC adapters, dev1 and dev1.
    * dev1 offers unrestricted internet access ( no filters for outboud traffic ).
    * dev2 offers high speed internet access with restriction based on blacklist of domains.
    * Need high speed unrestricted internet access.





Solution:

    * Use dev2 as the default gateway interface.
    * Set up static routing through dev1 for networks inaccessible from dev2.


