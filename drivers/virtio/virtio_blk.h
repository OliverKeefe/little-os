#pragma once
#ifdef VIRTIO_BLK_H
#define VIRTIO_H

#include "../../common/common.h"

/* Feature Bits (for reference, see spec §5.2.3) */
#define VIRTIO_BLK_F_SIZE 1
#define VIRTIO_BLK_F_SEG_MAX 2
#define VIRTIO_BLK_F_RO 5
#define VIRTIO_BLK_F_BLK_SIZE 6
#define VIRTIO_BLK_F_FLUSH 9

/* Device configuration space (for reference, see spec §5.2.4) */
struct virtio_blk_config {
    uint64_t capacity;              /* capacity in 512-byte sectors */
    uint32_t size_max;
    uint32_t seg_max;
    struct virtio_blk_geometry {
        uint16_t cylinders;
        uint8_t  heads;
        uint8_t  sectors;
    } geometry;
    uint32_t blk_size;              /* if VIRTIO_BLK_F_BLK_SIZE */
    struct virtio_blk_topology {
        uint8_t  physical_block_exp;
        uint8_t  alignment_offset;
        uint16_t min_io_size;
        uint32_t opt_io_size;
    } topology;
    uint8_t  writeback;
    uint8_t  unused0;
    uint16_t num_queues;
    uint32_t max_discard_sectors;
    uint32_t max_discard_seg;
    uint32_t discard_sector_alignment;
    uint32_t max_write_zeroes_sectors;
    uint32_t max_write_zeroes_seg;
    uint8_t  write_zeroes_may_unmap;
    uint8_t  unused1[3];
    uint32_t max_secure_erase_sectors;
    uint32_t max_secure_erase_seg;
    uint32_t secure_erase_sector_alignment;
    struct virtio_blk_zoned_characteristics {
        uint32_t zone_sectors;
        uint32_t max_open_zones;
        uint32_t max_active_zones;
        uint32_t max_append_sectors;
        uint32_t write_granularity;
        uint8_t  model;
        uint8_t  unused2[3];
    } zoned;
} __attribute__((packed));

#define VIRTIO_BLK_T_IN 0
#define VIRTIO_BLK_T_OUT 1
#define VIRTIO_BLK_T_FLUSH 4

struct virtio_blk_outhdr {
    uint32_t type;
    uint32_t ioprio;
    uint64_t sector;
} __attribute__((packed));

#define VIRTIO_BLK_S_OK 0
#define VIRTIO_BLK_S_IOERR 1
#define VIRTIO_BLK_S_UNSUPP 2

#define SECTOR_SIZE 512

struct virtio_blk_req {
    uint32_t type;
    uint32_t reserved;
    uint64_t sector;
    uint8_t  data[SECTOR_SIZE];
    uint8_t  status;
} __attribute__((packed));

#define VIRTIO_BLK_PADDR 0x10001000
