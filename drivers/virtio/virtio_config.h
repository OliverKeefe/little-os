#ifndef VIRTIO_CONFIG_H
#define VIRTIO_CONFIG_H

struct virtio_blk_config {
    le64 capacity;
    le32 size_max;
    le32 seg_max;
    struct virtio_blk_geometry {
        le16 cylinders;
        u8 heads;
        u8 sectors;
    } geometry;
    le32 blk_size;
    struct virtio_blk_topology {
        // # of logical blocks per physical block (log2)
        u8 physical_block_exp;
        // offset of first aligned logical block
        u8 alignment_offset;
        // suggested minimum I/O size in blocks
        le16 min_io_size;
        // optimal (suggested maximum) I/O size in blocks
        le32 opt_io_size;
    } topology;
    u8 writeback;
    u8 unused0;
    u16 num_queues;
    le32 max_discard_sectors;
    le32 max_discard_seg;
    le32 discard_sector_alignment;
    le32 max_write_zeroes_sectors;
    le32 max_write_zeroes_seg;
    u8 write_zeroes_may_unmap;
    u8 unused1[3];
    le32 max_secure_erase_sectors;
    le32 max_secure_erase_seg;
    le32 secure_erase_sector_alignment;
    struct virtio_blk_zoned_characteristics {
        le32 zone_sectors;
        le32 max_open_zones;
        le32 max_active_zones;
        le32 max_append_sectors;
        le32 write_granularity;
        u8 model;
        u8 unused2[3];
    } zoned;
};

#endif // VIRTIO_CONFIG_H