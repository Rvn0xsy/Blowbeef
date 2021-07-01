# Blowbeef
BlowBeef is a tool for analyzing WMI data.

## Usage

```
BlowBeef is a tool for analyzing WMI data. @Rvn0xsy
Usage: blowbeef.exe [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
  -f,--file TEXT:FILE         Analysis rules file.
  -o,--output TEXT            Output file.
  -m,--modules ENUM:value in {All->0,DISK_Volume->6,DNS_Cache->2,Net_IPAddress->4,Net_Route->3,Net_TCPConnection->5,Process->1,Product->7} OR {0,6,2,4,3,5,1,7} REQUIRED
                              Module name.
```

## Modules

- All->0
- DISK_Volume->6
- DNS_Cache->2
- Net_IPAddress->4
- Net_Route->3
- Net_TCPConnection->5
- Process->1
- Product->7

DNS_Cache Example: `blowbeef.exe -m 2`

```
> blowbeef.exe -m 2 -f C:\blowbeef.toml
2021-06-30 21:08:16,512 INFO [default] Connected to Root\StandardCimv2 WMI namespace
2021-06-30 21:08:16,513 INFO [default] Query Execute Success. Query is : select * from MSFT_DNSClientCache
2021-06-30 21:08:16,583 INFO [default] Get Rows Data :2
Data            Name
34.*.*.8             tr.*.com
185.199.108.133         user-images.githubusercontent.com
185.199.109.133         user-images.githubusercontent.com
185.199.110.133         user-images.githubusercontent.com
185.199.111.133         user-images.githubusercontent.com
*-pme.azureedge.net     *.vo.msecnd.net
*-pme.ec.azureedge.net  *-pme.azureedge.net
cs9.wpc.v0cdn.net       *-pme.ec.azureedge.net
202.89.233.101          china.bing123.com
202.89.233.100          china.bing123.com
```

