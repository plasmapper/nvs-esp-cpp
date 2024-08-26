NVS Component
=============

.. |COMPONENT| replace:: nvs

.. |ESP_IDF_VERSION| replace:: 5.0
   
.. |VERSION| replace:: 1.0.0

.. include:: ../../../installation.rst

.. include:: ../../../sdkconfig_common.rst

Features
--------

1. :cpp:class:`PL::NvsNamespace` - an NVS namespace class. It is initialized with a namespace name and a partition name (optional).
   A number of :cpp:func:`PL::NvsNamespace::Read` and :cpp:func:`PL::NvsNamespace::Write` functions read and write from/to the NVS.
   :cpp:func:`PL::NvsNamespace::Erase` functions erase one or all values. :cpp:func:`PL::NvsNamespace::Commit` writes any pending changes to the NVS. 

Thread safety
-------------

Class method thread safety is implemented by having the :cpp:class:`PL::Lockable` as a base class and creating the class object lock guard at the beginning of the methods.

API reference
-------------

.. toctree::
  
  api/types      
  api/nvs_namespace