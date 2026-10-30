#include "virtio.h"
#include "../../kernel/kernel.h"

static void write_vq_index(const unsigned reg_queue_sel, const int idx) {
    virtio_reg_write32(reg_queue_sel, idx);
}

static void write_vq_size(const unsigned reg_queue_num, const int entry_num) {
    virtio_reg_write32(reg_queue_num, entry_num);
}

static void write_phys_page_frame(const unsigned reg_queue_pfn, const int page_frame_num) {
    virtio_reg_write32(reg_queue_pfn, page_frame_num);
}

struct virtio_virtq *virtq_init(unsigned index) {
    paddr_t virtq_paddr = alloc_pages(align_up(sizeof(struct virtio_virtq), PAGE_SIZE) / PAGE_SIZE);

    struct virtio_virtq *vq = (struct virtio_virtq *) virtq_paddr;
    vq->queue_index = index;
    vq->used_index = (volatile uint16_t *) &vq->used.index;
    write_vq_index(VIRTIO_REG_QUEUE_SEL, index);
    write_vq_size(VIRTIO_REG_QUEUE_NUM, VIRTQ_ENTRY_NUM);
    write_phys_page_frame(VIRTIO_REG_QUEUE_PFN, virtq_paddr / PAGE_SIZE);

    return vq;
}