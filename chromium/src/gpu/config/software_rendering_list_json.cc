// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Determines whether certain gpu-related features are blacklisted or not.
// A valid software_rendering_list.json file are in the format of
// {
//   "version": "x.y",
//   "entries": [
//     { // entry 1
//     },
//     ...
//     { // entry n
//     }
//   ]
// }
//
// Each entry contains the following fields (fields are optional unless
// specifically described as mandatory below):
// 1. "id" is an integer.  0 is reserved.  This field is mandatory.
// 2. "os" contains "type" and an optional "version". "type" could be "macosx",
//    "linux", "win", "chromeos", or "any".  "any" is the same as not specifying
//    "os".
//    "version" is a VERSION structure (defined below).
// 3. "vendor_id" is a string.  0 is reserved.
// 4. "device_id" is an array of strings.  0 is reserved.
// 5. "multi_gpu_style" is a string, valid values include "optimus", and
//    "amd_switchable".
// 6. "multi_gpu_category" is a string, valid values include "any", "primary",
//    and "secondary".  If unspecified, the default value is "primary".
// 7. "driver_vendor" is a STRING structure (defined below).
// 8. "driver_version" is a VERSION structure (defined below).
// 9. "driver_date" is a VERSION structure (defined below).
//    The version is interpreted as "year.month.day".
// 10. "gl_vendor" is a STRING structure (defined below).
// 11. "gl_renderer" is a STRING structure (defined below).
// 12. "gl_extensions" is a STRING structure (defined below).
// 13. "perf_graphics" is a FLOAT structure (defined below).
// 14. "perf_gaming" is a FLOAT structure (defined below).
// 15. "perf_overall" is a FLOAT structure (defined below).
// 16. "machine_model" contais "name" and an optional "version".  "name" is a
//     STRING structure and "version" is a VERSION structure (defined below).
// 17. "gpu_count" is a INT structure (defined below).
// 18  "cpu_info" is a STRING structure (defined below).
// 19. "exceptions" is a list of entries.
// 20. "features" is a list of gpu feature strings, valid values include
//     "accelerated_2d_canvas", "accelerated_compositing", "webgl",
//     "multisampling", "flash_3d", "flash_stage3d", "texture_sharing",
//     "accelerated_video", "accelerated_video_decode", "panel_fitting",
//     "force_compositing_mode", and "all".
//     This field is mandatory.
// 21. "description" has the description of the entry.
// 22. "webkit_bugs" is an array of associated webkit bug numbers.
// 23. "cr_bugs" is an array of associated webkit bug numbers.
// 24. "browser_version" is a VERSION structure (defined below).  If this
//     condition is not satisfied, the entry will be ignored.  If it is not
//     present, then the entry applies to all versions of the browser.
// 25. "disabled" is a boolean. If it is present, the entry will be skipped.
//     This can not be used in exceptions.
//
// VERSION includes "op", "style", "number", and "number2".  "op" can be any of
// the following values: "=", "<", "<=", ">", ">=", "any", "between".  "style"
// is optional and can be "lexical" or "numerical"; if it's not specified, it
// defaults to "numerical".  "number2" is only used if "op" is "between".
// "between" is "number <= * <= number2".
// "number" is used for all "op" values except "any". "number" and "number2"
// are in the format of x, x.x, x.x.x, etc.
// Only "driver_version" supports lexical style if the format is major.minor;
// in that case, major is still numerical, but minor is lexical. 
//
// STRING includes "op" and "value".  "op" can be any of the following values:
// "contains", "beginwith", "endwith", "=".  "value" is a string.
//
// FLOAT includes "op" "value", and "value2".  "op" can be any of the
// following values: "=", "<", "<=", ">", ">=", "any", "between".  "value2" is
// only used if "op" is "between".  "value" is used for all "op" values except
// "any". "value" and "value2" are valid float numbers.
// INT is very much like FLOAT, except that the values need to be integers.

#include "gpu/config/gpu_control_list_jsons.h"

#define LONG_STRING_CONST(...) #__VA_ARGS__

namespace gpu {

const char kSoftwareRenderingListJson[] = LONG_STRING_CONST(

{
  "name": "software rendering list",
  // Please update the version number whenever you change this file.
  "version": "6.2",
  "entries": [
    // Put all opera entries at the start to reduce merge conflicts.
    {
      "id": 1000,
      "description": "WebGL doesn't work on older Qualcomm Adreno.",
      "opera_bugs": ["WAM-613"],
      "os": {
        "type": "android"
      },
      "gl_renderer": {
        "op": "contains",
        "value": "Adreno"
      },
      "driver_version": {
        "op": "<",
        "number": "6.0"
      },
      "features": [
        "webgl"
      ]
    },
    {
      "id": 1,
      "description": "ATI Radeon X1900 is not compatible with WebGL on the Mac.",
      "webkit_bugs": [47028],
      "os": {
        "type": "macosx"
      },
      "vendor_id": "0x1002",
      "device_id": ["0x7249"],
      "features": [
        "webgl",
        "flash_3d",
        "flash_stage3d"
      ]
    },
    {
      "id": 3,
      "description": "GL driver is software rendered. Accelerated compositing is disabled.",
      "cr_bugs": [59302],
      "os": {
        "type": "linux"
      },
      "gl_renderer": {
        "op": "contains",
        "value": "software"
      },
      "features": [
        "accelerated_compositing"
      ]
    },
    {
      "id": 4,
      "description": "The Intel Mobile 945 Express family of chipsets is not compatible with WebGL.",
      "cr_bugs": [232035],
      "os": {
        "type": "any"
      },
      "vendor_id": "0x8086",
      "device_id": ["0x27AE"],
      "features": [
        "webgl",
        "flash_3d",
        "flash_stage3d",
        "accelerated_2d_canvas"
      ]
    },
    {
      "id": 5,
      "description": "ATI/AMD cards with older or third-party drivers in Linux are crash-prone.",
      "cr_bugs": [71381, 76428, 73910, 101225, 136240],
      "os": {
        "type": "linux"
      },
      "vendor_id": "0x1002",
      "exceptions": [
        {
          "driver_vendor": {
            "op": "contains",
            "value": "AMD"
          },
          "driver_version": {
            "op": ">=",
            "style": "lexical",
            "number": "8.98"
          }
        }
      ],
      "features": [
        "all"
      ]
    },
    {
      "id": 8,
      "description": "NVIDIA GeForce FX Go5200 is assumed to be buggy.",
      "cr_bugs": [72938],
      "os": {
        "type": "any"
      },
      "vendor_id": "0x10de",
      "device_id": ["0x0324"],
      "features": [
        "all"
      ]
    },
    {
      "id": 10,
      "description": "NVIDIA GeForce 7300 GT on Mac does not support WebGL.",
      "cr_bugs": [73794],
      "os": {
        "type": "macosx"
      },
      "vendor_id": "0x10de",
      "device_id": ["0x0393"],
      "features": [
        "webgl",
        "flash_3d",
        "flash_stage3d"
      ]
    },
    {
      "id": 12,
      "description": "Drivers older than 2009-01 on Windows are possibly unreliable.",
      "cr_bugs": [72979, 89802],
      "os": {
        "type": "win"
      },
      "driver_date": {
        "op": "<",
        "number": "2009.1"
      },
      "exceptions": [
        {
          "vendor_id": "0x8086",
          "device_id": ["0x29a2"],
          "driver_version": {
            "op": ">=",
            "number": "7.15.10.1624"
          }
        }
      ],
      "features": [
        "accelerated_2d_canvas",
        "accelerated_video",
        "accelerated_video_decode",
        "3d_css",
        "multisampling",
        "flash_3d",
        "force_compositing_mode"
      ]
    },
    {
      "id": 13,
      "description": "ATI drivers older than 10.6 on Windows XP are possibly unreliable.",
      "cr_bugs": [74212],
      "os": {
        "type": "win",
        "version": {
          "op": "=",
          "number": "5"
        }
      },
      "vendor_id": "0x1002",
      "driver_version": {
        "op": "<",
        "number": "8.741"
      },
      "features": [
        "accelerated_video",
        "accelerated_video_decode",
        "3d_css",
        "multisampling",
        "flash_3d",
        "force_compositing_mode"
      ]
    },
    {
      "id": 14,
      "description": "NVIDIA drivers older than 257.21 on Windows XP are possibly unreliable.",
      "cr_bugs": [74212],
      "os": {
        "type": "win",
        "version": {
          "op": "=",
          "number": "5"
        }
      },
      "vendor_id": "0x10de",
      "driver_version": {
        "op": "<",
        "number": "6.14.12.5721"
      },
      "features": [
        "accelerated_video",
        "accelerated_video_decode",
        "3d_css",
        "multisampling",
        "flash_3d",
        "force_compositing_mode"
      ]
    },
    {
      "id": 15,
      "description": "Intel drivers older than 14.42.7.5294 on Windows XP are possibly unreliable.",
      "cr_bugs": [74212],
      "os": {
        "type": "win",
        "version": {
          "op": "=",
          "number": "5"
        }
      },
      "vendor_id": "0x8086",
      "driver_version": {
        "op": "<",
        "number": "6.14.10.5294"
      },
      "features": [
        "accelerated_video",
        "accelerated_video_decode",
        "3d_css",
        "multisampling",
        "flash_3d",
        "force_compositing_mode"
      ]
    },
    {
      "id": 16,
      "description": "Multisampling is buggy in ATI cards on older MacOSX.",
      "cr_bugs": [67752, 83153],
      "os": {
        "type": "macosx",
        "version": {
          "op": "<",
          "number": "10.7.2"
        }
      },
      "vendor_id": "0x1002",
      "features": [
        "multisampling"
      ]
    },
    {
      "id": 17,
      "description": "Intel mesa drivers are crash-prone.",
      "cr_bugs": [76703, 164555, 225200],
      "os": {
        "type": "linux"
      },
      "vendor_id": "0x8086",
      "exceptions": [
        {
          "device_id": ["0x0102", "0x0106", "0x0112", "0x0116", "0x0122", "0x0126", "0x010a", "0x0152", "0x0156", "0x015a", "0x0162", "0x0166"],
          "driver_version": {
            "op": ">=",
            "number": "8.0"
          }
        },
        {
          "device_id": ["0xa001", "0xa002", "0xa011", "0xa012", "0x29a2", "0x2992", "0x2982", "0x2972", "0x2a12", "0x2a42", "0x2e02", "0x2e12", "0x2e22", "0x2e32", "0x2e42", "0x2e92"],
          "driver_version": {
            "op": ">",
            "number": "8.0.2"
          }
        },
        {
          "device_id": ["0x0042", "0x0046"],
          "driver_version": {
            "op": ">",
            "number": "8.0.4"
          }
        },
        {
          "device_id": ["0x2a02"],
          "driver_version": {
            "op": ">=",
            "number": "9.1"
          }
        }
      ],
      "features": [
        "all"
      ]
    },
    {
      "id": 18,
      "description": "NVIDIA Quadro FX 1500 is buggy.",
      "cr_bugs": [84701],
      "os": {
        "type": "linux"
      },
      "vendor_id": "0x10de",
      "device_id": ["0x029e"],
      "features": [
        "all"
      ]
    },
    {
      "id": 19,
      "description": "GPU acceleration is no longer supported in Leopard.",
      "cr_bugs": [87157, 130495],
      "os": {
        "type": "macosx",
        "version": {
          "op": "=",
          "number": "10.5"
        }
      },
      "features": [
        "all"
      ]
    },
    {
      "id": 23,
      "description": "Mesa drivers in linux older than 7.11 are assumed to be buggy.",
      "os": {
        "type": "linux"
      },
      "driver_vendor": {
        "op": "=",
        "value": "Mesa"
      },
      "driver_version": {
        "op": "<",
        "number": "7.11"
      },
      "features": [
        "all"
      ]
    },
    {
      "id": 24,
      "description": "Accelerated 2d canvas is unstable in Linux at the moment.",
      "os": {
        "type": "linux"
      },
      "features": [
        "accelerated_2d_canvas"
      ]
    },
    {
      "id": 27,
      "description": "ATI/AMD cards with older drivers in Linux are crash-prone.",
      "cr_bugs": [95934, 94973, 136240],
      "os": {
        "type": "linux"
      },
      "gl_vendor": {
        "op": "beginwith",
        "value": "ATI"
      },
      "exceptions": [
        {
          "driver_vendor": {
            "op": "contains",
            "value": "AMD"
          },
          "driver_version": {
            "op": ">=",
            "style": "lexical",
            "number": "8.98"
          }
        }
      ],
      "features": [
        "all"
      ]
    },
    {
      "id": 28,
      "description": "ATI/AMD cards with third-party drivers in Linux are crash-prone.",
      "cr_bugs": [95934, 94973],
      "os": {
        "type": "linux"
      },
      "gl_vendor": {
        "op": "beginwith",
        "value": "X.Org"
      },
      "gl_renderer": {
        "op": "contains",
        "value": "AMD"
      },
      "features": [
        "all"
      ]
    },
    {
      "id": 29,
      "description": "ATI/AMD cards with third-party drivers in Linux are crash-prone.",
      "cr_bugs": [95934, 94973],
      "os": {
        "type": "linux"
      },
      "gl_vendor": {
        "op": "beginwith",
        "value": "X.Org"
      },
      "gl_renderer": {
        "op": "contains",
        "value": "ATI"
      },
      "features": [
        "all"
      ]
    },
    {
      "id": 30,
      "description": "NVIDIA cards with nouveau drivers in Linux are crash-prone.",
      "cr_bugs": [94103],
      "os": {
        "type": "linux"
      },
      "vendor_id": "0x10de",
      "gl_vendor": {
        "op": "beginwith",
        "value": "nouveau"
      },
      "features": [
        "all"
      ]
    },
    {
      "id": 32,
      "description": "Accelerated 2d canvas is disabled on Windows systems with low perf stats.",
      "cr_bugs": [116350, 151500],
      "os": {
        "type": "win"
      },
      "perf_overall": {
        "op": "<",
        "value": "3.5"
      },
      "exceptions": [
        {
          "perf_gaming": {
            "op": ">",
            "value": "3.5"
          }
        },
        {
          "cpu_info": {
            "op": "contains",
            "value": "Atom"
          }
        }
      ],
      "features": [
        "accelerated_2d_canvas"
      ]
    },
    {
      "id": 33,
      "description": "Multisampling is buggy in Intel IvyBridge.",
      "cr_bugs": [116370],
      "os": {
        "type": "linux"
      },
      "vendor_id": "0x8086",
      "device_id": ["0x0152", "0x0156", "0x015a", "0x0162", "0x0166"],
      "features": [
          "multisampling"
      ]
    },
    {
      "id": 34,
      "description": "S3 Trio (used in Virtual PC) is not compatible.",
      "cr_bugs": [119948],
      "os": {
        "type": "win"
      },
      "vendor_id": "0x5333",
      "device_id": ["0x8811"],
      "features": [
        "all"
      ]
    },
    {
      "id": 35,
      "description": "Stage3D is not supported on Linux.",
      "cr_bugs": [129848],
      "os": {
        "type": "linux"
      },
      "features": [
        "flash_stage3d"
      ]
    },
    {
      "id": 37,
      "description": "Drivers are unreliable for Optimus on Linux.",
      "cr_bugs": [131308],
      "os": {
        "type": "linux"
      },
      "multi_gpu_style": "optimus",
      "features": [
        "all"
      ]
    },
    {
      "id": 38,
      "description": "Accelerated 2D canvas is unstable for NVidia GeForce 9400M on Lion.",
      "cr_bugs": [130495],
      "os": {
        "type": "macosx",
        "version": {
          "op": "=",
          "number": "10.7"
        }
      },
      "vendor_id": "0x10de",
      "device_id": ["0x0863"],
      "features": [
        "accelerated_2d_canvas"
      ]
    },
    {
      "id": 41,
      "description": "Disable 3D (but not Stage3D) in Flash on XP",
      "cr_bugs": [134885],
      "os": {
        "type": "win",
        "version": {
          "op": "=",
          "number": "5"
        }
      },
      "features": [
        "flash_3d"
      ]
    },
    {
      "id": 42,
      "description": "AMD Radeon HD 6490M on Snow Leopard is buggy.",
      "cr_bugs": [137307],
      "os": {
        "type": "macosx",
        "version": {
          "op": "=",
          "number": "10.6"
        }
      },
      "vendor_id": "0x1002",
      "device_id": ["0x6760"],
      "features": [
        "webgl"
      ]
    },
    {
      "id": 43,
      "description": "Intel driver version 8.15.10.1749 has problems sharing textures.",
      "cr_bugs": [133924],
      "os": {
        "type": "win"
      },
      "vendor_id": "0x8086",
      "driver_version": {
        "op": "=",
        "number": "8.15.10.1749"
      },
      "features": [
        "texture_sharing"
      ]
    },
    {
      "id": 44,
      "description": "Intel HD 4000 causes kernel panic on Lion.",
      "cr_bugs": [134015],
      "os": {
        "type": "macosx",
        "version": {
          "op": "between",
          "number": "10.7.0",
          "number2": "10.7.4"
        }
      },
      "vendor_id": "0x8086",
      "device_id": ["0x0166"],
      "multi_gpu_category": "any",
      "features": [
        "all"
      ]
    },
    {
      "id": 45,
      "description": "Parallels drivers older than 7 are buggy.",
      "cr_bugs": [138105],
      "os": {
        "type": "win"
      },
      "vendor_id": "0x1ab8",
      "driver_version": {
        "op": "<",
        "number": "7"
      },
      "features": [
        "all"
      ]
    },
    {
      "id": 46,
      "description": "ATI FireMV 2400 cards on Windows are buggy.",
      "cr_bugs": [124152],
      "os": {
        "type": "win"
      },
      "vendor_id": "0x1002",
      "device_id": ["0x3151"],
      "features": [
        "all"
      ]
    },
    {
      "id": 47,
      "description": "NVIDIA linux drivers older than 295.* are assumed to be buggy.",
      "cr_bugs": [78497],
      "os": {
        "type": "linux"
      },
      "vendor_id": "0x10de",
      "driver_vendor": {
        "op": "=",
        "value": "NVIDIA"
      },
      "driver_version": {
        "op": "<",
        "number": "295"
      },
      "features": [
        "all"
      ]
    },
    {
      "id": 48,
      // Please keep in sync with content/test/content_browser_test.cc.
      "description": "Accelerated video decode is unavailable on Mac and Linux.",
      "cr_bugs": [137247, 133828],
      "exceptions": [
        {
          "os": {
            "type": "chromeos"
          }
        },
        {
          "os": {
            "type": "win"
          }
        }
      ],
      "features": [
        "accelerated_video_decode"
      ]
    },
    {
      "id": 49,
      "description": "NVidia GeForce GT 650M can cause the system to hang with flash 3D.",
      "cr_bugs": [140175],
      "os": {
        "type": "macosx",
        "version": {
          "op": "between",
          "number": "10.8.0",
          "number2": "10.8.1"
        }
      },
      "multi_gpu_style": "optimus",
      "vendor_id": "0x10de",
      "device_id": ["0x0fd5"],
      "features": [
        "flash_3d",
        "flash_stage3d"
      ]
    },
    {
      "id": 50,
      "description": "Disable VMware software renderer.",
      "cr_bugs": [145531],
      "os": {
        "type": "linux"
      },
      "gl_vendor": {
        "op": "beginwith",
        "value": "VMware"
      },
      "features": [
        "all"
      ]
    },
    {
      "id": 51,
      "description": "NVIDIA drivers 6.14.11.9621 is buggy on Windows XP.",
      "cr_bugs": [152096],
      "os": {
        "type": "win",
        "version": {
          "op": "=",
          "number": "5"
        }
      },
      "vendor_id": "0x10de",
      "driver_version": {
        "op": "=",
        "number": "6.14.11.9621"
      },
      "features": [
        "all"
      ]
    },
    {
      "id": 52,
      "description": "NVIDIA drivers 6.14.11.8267 is buggy on Windows XP.",
      "cr_bugs": [152096],
      "os": {
        "type": "win",
        "version": {
          "op": "=",
          "number": "5"
        }
      },
      "vendor_id": "0x10de",
      "driver_version": {
        "op": "=",
        "number": "6.14.11.8267"
      },
      "features": [
        "all"
      ]
    },
    {
      "id": 53,
      "description": "The Intel GMA500 is too slow for Stage3D.",
      "cr_bugs": [152096],
      "vendor_id": "0x8086",
      "device_id": ["0x8108", "0x8109"],
      "features": [
        "flash_stage3d"
      ]
    },
    {
      "id": 55,
      "description": "Drivers older than 2007-01 on Windows are assumed to be buggy.",
      "cr_bugs": [72979, 89802],
      "os": {
        "type": "win"
      },
      "driver_date": {
        "op": "<",
        "number": "2007.1"
      },
      "exceptions": [
        {
          "vendor_id": "0x8086",
          "device_id": ["0x29a2"],
          "driver_version": {
            "op": ">=",
            "number": "7.15.10.1624"
          }
        }
      ],
      "features": [
        "all"
      ]
    },
    {
      "id": 56,
      "description": "NVIDIA linux drivers are unstable when using multiple Open GL contexts and with low memory.",
      "cr_bugs": [145600],
      "os": {
        "type": "linux"
      },
      "vendor_id": "0x10de",
      "driver_vendor": {
        "op": "=",
        "value": "NVIDIA"
      },
      "features": [
        "accelerated_video",
        "accelerated_video_decode",
        "flash_3d",
        "flash_stage3d"
      ]
    },
    {
      // Panel fitting is only used with OS_CHROMEOS. To avoid displaying an
      // error in chrome:gpu on every other platform, this blacklist entry needs
      // to only match on chromeos. The drawback is that panel_fitting will not
      // appear to be blacklisted if accidentally queried on non-chromeos.
      "id": 57,
      "description": "Chrome OS panel fitting is only supported for Intel IVB and SNB Graphics Controllers.",
      "os": {
        "type": "chromeos"
      },
      "exceptions": [
        {
          "vendor_id": "0x8086",
          "device_id": ["0x0106", "0x0116", "0x0166"]
        }
      ],
      "features": [
        "panel_fitting"
      ]
    },
    {
      "id": 59,
      "description": "NVidia driver 8.15.11.8593 is crashy on Windows.",
      "cr_bugs": [155749],
      "os": {
        "type": "win"
      },
      "vendor_id": "0x10de",
      "driver_version": {
        "op": "=",
        "number": "8.15.11.8593"
      },
      "features": [
        "accelerated_video_decode"
      ]
    },
    {
      "id": 60,
      "description": "Multisampling is buggy on Mac with NVIDIA gpu prior to 10.8.3.",
      "cr_bugs": [137303],
      "os": {
        "type": "macosx",
        "version": {
          "op": "<",
          "number": "10.8.3"
        }
      },
      "vendor_id": "0x10de",
      "features": [
        "multisampling"
      ]
    },
    {
      "id": 61,
      "description": "Multisampling is buggy on Mac with Intel gpu prior to 10.8.3.",
      "cr_bugs": [137303],
      "os": {
        "type": "macosx",
        "version": {
          "op": "<",
          "number": "10.8.3"
        }
      },
      "vendor_id": "0x8086",
      "features": [
        "multisampling"
      ]
    },
    {
      "id": 62,
      "description": "Accelerated 2D canvas buggy on old Qualcomm Adreno.",
      "cr_bugs": [161575],
      "os": {
        "type": "android"
      },
      "gl_renderer": {
        "op": "contains",
        "value": "Adreno"
      },
      "driver_version": {
        "op": "<",
        "number": "4.1"
      },
      "features": [
        "accelerated_2d_canvas"
      ]
    },
    {
      "id": 63,
      "description": "Multisampling is buggy on Mac with AMD gpu prior to 10.8.3.",
      "cr_bugs": [162466],
      "os": {
        "type": "macosx",
        "version": {
          "op": "<",
          "number": "10.8.3"
        }
      },
      "vendor_id": "0x1002",
      "features": [
        "multisampling"
      ]
    },
    {
      "id": 1001,
      "description": "WebGL is unstable on Broadcom GPUs and can crash the whole OS.",
      "opera_bugs": ["WAM-1678"],
      "os": {
        "type": "android"
      },
      "gl_renderer": {
        "op": "contains",
        "value": "VideoCore"
      },
      "features": [
        "webgl"
      ]
    },
    {
      "id": 64,
      "description": "Hardware video decode is only supported in win7+.",
      "cr_bugs": [159458],
      "os": {
        "type": "win",
        "version": {
          "op": "<",
          "number": "6.1"
        }
      },
      "features": [
        "accelerated_video_decode"
      ]
    },

    {
      "id": 65,
      "description": "Force compositing mode is unstable in Win Vista.",
      "cr_bugs": [170421],
      "os": {
        "type": "win",
        "version": {
          "op": "=",
          "number": "6.0"
        }
      },
      "features": [
        "force_compositing_mode"
      ]
    },
    {
      "id": 66,
      "description": "Force compositing mode is unstable in MacOSX earlier than 10.8.",
      "cr_bugs": [174101],
      "os": {
        "type": "macosx",
        "version": {
          "op": "<",
          "number": "10.8"
        }
      },
      "features": [
        "force_compositing_mode"
      ]
    },
    {
      "id": 67,
      "description": "Accelerated 2D Canvas is not supported on WinXP.",
      "cr_bugs": [175149],
      "os": {
        "type": "win",
        "version": {
          "op": "=",
          "number": "5"
        }
      },
      "features": [
        "accelerated_2d_canvas"
      ]
    },
    {
      "id": 68,
      "description": "VMware Fusion 4 has corrupt rendering with Win Vista+.",
      "cr_bugs": [169470],
      "os": {
        "type": "win",
        "version": {
          "op": ">=",
          "number": "6.0"
        }
      },
      "vendor_id": "0x15ad",
      "driver_version": {
        "op": "<=",
        "number": "7.14.1.1134"
      },
      "features": [
        "all"
      ]
    },
    {
      "id": 69,
      "description": "NVIDIA driver 8.17.11.9621 is buggy with Stage3D baseline mode.",
      "cr_bugs": [172771],
      "os": {
        "type": "win"
      },
      "vendor_id": "0x10de",
      "driver_version": {
        "op": "=",
        "number": "8.17.11.9621"
      },
      "features": [
        "flash_stage3d_baseline"
      ]
    },
    {
      "id": 70,
      "description": "NVIDIA driver 8.17.11.8267 is buggy with Stage3D baseline mode.",
      "cr_bugs": [172771],
      "os": {
        "type": "win"
      },
      "vendor_id": "0x10de",
      "driver_version": {
        "op": "=",
        "number": "8.17.11.8267"
      },
      "features": [
        "flash_stage3d_baseline"
      ]
    },
    {
      "id": 71,
      "description": "All Intel drivers before 8.15.10.2021 are buggy with Stage3D baseline mode.",
      "cr_bugs": [172771],
      "os": {
        "type": "win"
      },
      "vendor_id": "0x8086",
      "driver_version": {
        "op": "<",
        "number": "8.15.10.2021"
      },
      "features": [
        "flash_stage3d_baseline"
      ]
    },
    {
      "id": 72,
      "description": "NVIDIA GeForce 6200 LE is buggy with WebGL.",
      "cr_bugs": [232529],
      "os": {
        "type": "win"
      },
      "vendor_id": "0x10de",
      "device_id": ["0x0163"],
      "features": [
        "webgl"
      ]
    },
)  // LONG_STRING_CONST macro
LONG_STRING_CONST(
    {
      "id": 73,
      "description": "WebGL is buggy with the NVIDIA GeForce GT 330M, 9400, and 9400M on MacOSX earlier than 10.8",
      "cr_bugs": [233523],
      "os": {
        "type": "macosx",
        "version": {
          "op": "<",
          "number": "10.8"
        }
      },
      "vendor_id": "0x10de",
      "device_id": ["0x0a29", "0x0861", "0x0863"],
      "features": [
        "webgl"
      ]
    },
    {
      "id": 74,
      "description": "GPU access is blocked if users don't have proper graphics driver installed after Windows installation",
      "cr_bugs": [248178],
      "os": {
        "type": "win"
      },
      "driver_vendor": {
        "op": "=",
        "value": "Microsoft"
      },
      "features": [
        "all"
      ]
    }
  ]
}

);  // LONG_STRING_CONST macro

}  // namespace gpu

