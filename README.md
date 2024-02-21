# IX-Ray

<div align="center">
  <p>
    <a href="https://github.com/ixray-team">
      <img src="https://github.com/ixray-team/ixray/raw/default/logo.png" alt="IX-Ray Team" width="150" height="150" />
    </a>
  </p>

  <p>
    <a href="https://github.com/ixray-team/ixray-1.6-stcop/releases/tag/r0.6">
      <img src="https://img.shields.io/github/v/release/ixray-team/ixray-1.6-stcop?include_prereleases&label=Release" alt="Latest release" />
    </a>
    <a href="https://github.com/ixray-team/ixray-1.6-stcop/actions/workflows/build-engine.yml">
      <img src="https://github.com/ixray-team/ixray-1.6-stcop/actions/workflows/build-engine.yml/badge.svg" alt="Build engine" />
    </a>
  </p>
</div>

Stable repository of the modernized _X-Ray_ 1.6 game engine

## Requirements

- Visual Studio 2022 Community Edition
  - MFC
  - C++/CLI
  - Windows SDK 10.0.19041.0+

## Building

Download the repository:

```console
git clone https://github.com/ixray-team/ixray-1.6-stcop.git
```

### Engine

- Build `XRay.Engine.slnf` on `Win32`

### Compressor

- Build `XRay.Compressor.slnf` on `Win32`

### Assets

- Run `generate-patch.bat` to get packed assets

## Changelog

All significant changes to this repository are documented in [this](CHANGELOG.md) file

## License

Contents of this repository licensed under terms of the custom MIT-like non-commercial license unless otherwise specified. See [this](./LICENSE.md) file for details

## Support

Project is being developed with the support of these tools

<div>
  <a href="https://pvs-studio.ru/ru/pvs-studio/?utm_source=website&utm_medium=github&utm_campaign=open_source" align="right">
    <img src="https://cdn.pvs-studio.com/static/images/logo/pvs_logo.png" alt="PVS-Studio" class="logo-footer" width="72" align="left" />
  </a>

  <br/>

  [__PVS-Studio__](https://pvs-studio.ru/ru/pvs-studio/?utm_source=website&utm_medium=github&utm_campaign=open_source) - static analyzer for C, C++, C#, and Java code
</div>
