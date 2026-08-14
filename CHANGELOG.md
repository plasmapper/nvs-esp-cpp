# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]
### Changed
- String read to use PL::Buffer instead of std::unique_ptr.

## [1.1.0] - 2026-08-10
### Added
- ESP-IDF v6.0 support.

## [1.0.1] - 2026-08-07
### Added
- Example.

### Changed
- Lock timeout handling.
- NvsNamespace::Write string overload to take value by const reference.

### Fixed
- Deprecated nvs_handle type.
- Getting NVS blob actual size in NvsNamespace::Read.
- NvsNamespace 2-parameter constructor not validating access mode.
- Silently discarded commit error in NvsNamespace destructor.

## [1.0.0] - 2024-06-12
Initial release.