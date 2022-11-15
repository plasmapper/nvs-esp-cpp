NVS Component
=============

.. |COMPONENT| replace:: nvs

.. include:: ../../../installation.rst

.. include:: ../../../sdkconfig_common.rst

Features
--------

1. :cpp:class:`PL::NvsNamespace` - an NVS namespace class. It is initialized with a namespace name and a partition name (optional).
   A number of :cpp:func:`PL::NvsNamespace::Read` and :cpp:func:`PL::NvsNamespace::Write` functions read and write from/to the NVS.
   :cpp:func:`PL::NvsNamespace::Erase` functions erase one or all values. :cpp:func:`PL::NvsNamespace::Commit` writes any pending changes to the NVS. 

API reference
-------------

.. toctree::
  
  api/types      
  api/nvs_namespace